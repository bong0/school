#include <ncurses.h>
#include <stdlib.h>
#include <termcap.h> //better: terminfo
#include <string.h>
#include <unistd.h> // usleep
#include <time.h> // time in srand
#include <panel.h> //simplify layer handling
#include "snake_rw.h"

int main(int argc, char **argv){
	/*
	 * Init Variables
	 */
	WINDOW *w_game = NULL; //game field
	WINDOW *w_gamefrm = NULL; // frame around the game field
	/* prepare panels in order */
	PANEL *p_game=NULL, *p_gamefrm=NULL;
	FILE *urandom;

	urandom = fopen("/dev/urandom", "rb");// treat as binary

	int *xPos, *yPos; //current x and y positions
	frame term, game;
	/*
	 * Gameplay Variables
	 */
	snake snk;
	xPos = &(snk.body[0][0]);
	yPos = &(snk.body[1][0]);
	snk.bodysym = ACS_BLOCK;
	snk.length=1;
	int cookie[2] = {0,0}; // stores cookie location x y; negative vals are invalid
	float speed = 150; // steps/ms
	char vector[2] = {0,0}; // movement vector x y
	int lastPos[2]; // store last position
	bool mod_length=FALSE;
	bool vec_diff=FALSE;

	/*
	 * Setup Terminal
	 */
	setup_term(&term, w_game);

	/*
	 * Setup Game Field
	 */
	w_game = prep_game(w_game, w_gamefrm, p_game, p_gamefrm, &game, &term, xPos, yPos, &snk);

	placeCookie(w_game, &game, cookie, urandom);
	getch();

	while(true){
		mvwprintw(stdscr, 22, 1, "snklen:%d", snk.length); 
		chdir_snake(w_game, &term, xPos, yPos, vector, &snk, &vec_diff);

		mod_length=mv_snake(w_game, &game, &term, &snk, xPos, yPos, vector, cookie, urandom, vec_diff);
		if(mod_length){
			xPos=&(snk.body[0][(snk.length)-1]); // need to renew position of head in arr
			yPos=&(snk.body[1][(snk.length)-1]);
		}
			
		debug(stdscr, &term, xPos, yPos);
		mvwprintw(stdscr, 5,1, "%d %d", snk.body[0][0], snk.body[1][0]);
		mvwprintw(stdscr, 6,1, "%d %d", snk.body[0][1], snk.body[1][1]);
		mvwprintw(stdscr, 7,1, "%d %d", snk.body[0][2], snk.body[1][2]);
		mvwprintw(stdscr, 8,1, "%d %d", snk.body[0][3], snk.body[1][3]);
		mvwprintw(stdscr, 9,1, "%d %d", snk.body[0][4], snk.body[1][4]);

		do_refresh(w_game, xPos, yPos, vector, &snk);
		wait(vector, &speed);
	}

 do_exit(urandom, 0);
 return 0;
}

bool chdir_snake(WINDOW *w_game, frame *term, int *xPos, int *yPos, char *vector, snake *snk, bool *vec_diff){
//TODO check if last vector is opposite of current nicht entgegen laufen
	int key; //last pressed key
	int lastvec[2] = {vector[0], vector[1]};
	fflush(stdin);
	key = getch();
    if(key != ERR){ // ERR is returned when no input is present currently
        if(key == 'q'|| key == 'Q'){ ask_quit(stdscr, term); do_refresh(w_game, xPos, yPos, NULL, snk); }
        switch(key){
            case KEY_UP: case 'k': case 8:
                    vector[0]=0;
                    vector[1]=-1;
                    break;
            case KEY_DOWN: case 'j': case 2:
                    vector[0]=0;
                    vector[1]= 1;
                    break;
            case KEY_LEFT: case 'h': case 4:
                    vector[0]= -1;
                    vector[1]=0;
                    break;
             case KEY_RIGHT: case 'l': case 6:
                    vector[0]=1;
                    vector[1]=0;
                    break;
             default:
                    inputStatus(stdscr, term, 1);
					*vec_diff=FALSE;
                    return FALSE; // no relevant keypress
        }
		if(((lastvec[0]==(vector[0]*-1)) || (lastvec[1]==(vector[1]*-1)))&&(lastvec[0]&&lastvec[1])){
			vector[0] = lastvec[0];
			vector[1] = lastvec[1];
		}
        inputStatus(stdscr, term, 0);
        return TRUE;
    }
	*vec_diff=FALSE;
    return FALSE; //nothing happened
}

bool mv_snake(WINDOW *w_game, frame *game, frame *term, snake *snake, int *xPos, int *yPos, char *vector, int cookie[], FILE *urandom, bool vec_diff){
	bool mod_length=FALSE;
	//save last head position
	snake->lastPos_h[0] = *xPos;
	snake->lastPos_h[1] = *yPos;
	//save last tail pos
	snake->lastPos_t[0] = snake->body[0][0];
	snake->lastPos_t[1] = snake->body[1][0];

	*xPos = snake->body[0][(snake->length)-1] + vector[0];
	*yPos = snake->body[1][(snake->length)-1] + vector[1];
	
	if(outOfBounds(xPos, yPos, game)){ //check whether new position is in the field
        hitFrame(term, urandom);
	}
	if(*yPos == cookie[1] && *xPos == cookie[0]){
		placeCookie(w_game, game, cookie, urandom);
		cookie[0]=-1; //invalidate position
		cookie[1]=-1;
		(snake->length)++;
		mod_length = TRUE;
		xPos=&(snake->body[0][(snake->length)-1]); // need to renew position of head in arr temporary
		yPos=&(snake->body[1][(snake->length)-1]);
		*xPos = snake->lastPos_h[0];
		*yPos = snake->lastPos_h[1];
		return mod_length;
	}
	snake->body[0][(snake->length)-2] = snake->lastPos_h[0];
	snake->body[1][(snake->length)-2] = snake->lastPos_h[1];
	for(int i=0; i<(snake->length)-1; i++){ //move all snake elements one pos left
		snake->body[0][i] = snake->body[0][i+1];
		snake->body[1][i] = snake->body[1][i+1];
	}

	return mod_length;
}
bool outOfBounds(int *xPos, int *yPos, frame *frm_game){
	if(*xPos >= frm_game->cols || *xPos < 0){
			return 1;
	}
	else if(*yPos >= frm_game->lines || *yPos < 0){
			return 1;
	}
	else return 0;
}
void hitFrame(frame *frm, FILE *urandom){
    draw_stats(frm, urandom);
 	return; //stub
}
void placeCookie(WINDOW *win, frame *frm, int *cookie, FILE *urandom){
	//collect a seed from urandom
	void *chunk = (unsigned int*)malloc(sizeof(int));
	fread(chunk, 4,1, urandom);
	srand(*(unsigned int*)chunk);
	cookie[1]=(rand()%(frm->lines))+1;
    cookie[0]=(rand()%(frm->cols))+1;
	mvwprintw(stdscr, 24,1, "%d %d", cookie[0], cookie[1]);
    mvwaddch(win, cookie[1], cookie[0], ACS_DIAMOND); //ACS_DIAMOND
    return;
}
void do_refresh(WINDOW *w_game, int *xPos, int *yPos, char vector[], snake *snake){
	mvwaddch(w_game, snake->body[1][0], snake->body[0][0], ' '); //rm tail
	if((!(snake->lastPos_h[0]<0||snake->lastPos_h[1]<0)&&(snake->length)>1)){
		mvwaddch(w_game, snake->lastPos_h[1], snake->lastPos_h[0],'X' /*snake->bodysym*/); //replace old head w/ body sym
	}
	// draw head
    if(vector == NULL || (!vector[0] && !vector[1])) snake->headsym=ACS_BLOCK;
    else if(!vector[0] && vector[1]==1) snake->headsym=ACS_DARROW;
    else if(!vector[0] && vector[1]==-1) snake->headsym=ACS_UARROW;
    else if(vector[0]==-1 && !vector[1]) snake->headsym=ACS_LARROW;
    else snake->headsym=ACS_RARROW;
	mvwaddch(w_game, *yPos, *xPos, snake->headsym); // mv to new pos and place char

	mvwprintw(stdscr, 18,1, "lstpos_t: %d %d   ", snake->lastPos_t[0], snake->lastPos_t[1]); refresh();
	
	wrefresh(w_game);
	return;
}

void ask_quit(WINDOW *win, frame *frm){
    timeout(-1); //disable non blocking input
    mvwprintw(win, (frm->lines)-1,0, "Do you really want to Quit?[Y/n] ");
    echo(); fflush(stdin);
    switch(wgetch(win)){
        case '\n': case 'Y': case 'y': noecho(); do_exit(0);
        case 'n': case 'N': default:
            noecho(); //turn echoing off
            wmove(win, (frm->lines)-1, 0); //move to line beginning
            clrtoeol(); // clear line
            refresh();
            timeout(0); //reset to non blocking io
            return;
    }
}
void draw_border(WINDOW *win){
    wborder(win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
}
void draw_stats(frame *frm, FILE *urandom){ //TODO expand draw_stats
    WINDOW *w_stats;
    PANEL *p_stats;
    int size_x=30, size_y=10;
    w_stats = newwin(size_y, size_x,
                     (frm->centerY)-(size_y/2),
                     (frm->centerX)-(size_x/2));
    wclear(w_stats);
    draw_border(w_stats);
    p_stats = new_panel(w_stats);
    update_panels(); //order
    doupdate(); //show
    do_exit(urandom);
}
void wait(char *vector, float *speed){
    if(vector[0]!=0){
       usleep((*speed/2)*1000); // because columns are shorter than lines in my terminal
	}
	else{
        usleep(*speed*1000);
    }
    return;
}
void inputStatus(WINDOW *win, frame *frm, bool idle){
    if(idle){
        mvwprintw(win, 0, (frm->cols)-4, "Idle");
    }
    else{
        mvwprintw(win, 0, (frm->cols)-4, "    ");
    }
 refresh();
 return;

}
void setup_term(frame *term, WINDOW *w_game){
   	initscr(); //go into curses mode
	cbreak(); //disable input buffering
	noecho(); // disable output of chars put in
	keypad(stdscr, TRUE); //enable arrow keys and F-keys
    curs_set(0); // make cursor invisible
    timeout(0); // non blocking user input
	nodelay(w_game, TRUE);
	//nodelay(stdscr, TRUE);
	getmaxyx(stdscr, term->lines, term->cols); //get measurements of terminal
	//calc center
    term->centerX = (term->cols)/2;
    term->centerY = (term->lines)/2;
    return;
}
WINDOW* prep_game(WINDOW *w_game, WINDOW *w_gamefrm, PANEL *p_game, PANEL *p_gamefrm, frame *game, frame *term, int *xPos, int *yPos, snake *snake){
    if(term->lines > MAX_Y)
        game->lines = MAX_Y; //consider border!
    else
        game->lines = term->lines; //leave space for messages
    if(term->cols > MAX_X)
        game->cols = MAX_X; //consider border!
    else
        game->cols = term->cols;
	//calc center
    game->centerY = (game->lines)/2;
	game->centerX = (game->cols)/2;
	//create window in center
    w_game = newwin(game->lines, game->cols, //size
                    (term->centerY)-(game->centerY), //posY
                    (term->centerX)-game->centerX); //posX

    w_gamefrm = newwin((game->lines)+2, (game->cols)+2,
                    (term->centerY)-(game->centerY)-1,
                    (term->centerX)-(game->centerX)-1);
    draw_border(w_gamefrm);

    /* Stack Panels on top of each other w/p_game is on top*/
    p_gamefrm = new_panel(w_gamefrm);
    p_game = new_panel(w_game);

	update_panels(); // update order of panels | IMPORTANT: only after all wins are inited
    doupdate(); //show updated panels
	
    //move cursor to center
    *xPos=game->centerX;
    *yPos=game->centerY;

	//invalidate lastPos
	snake->lastPos_h[0] = -1;
	snake->lastPos_h[1] = -1;
	snake->lastPos_t[0] = -1;
	snake->lastPos_t[1] = -1;
    do_refresh(w_game, xPos, yPos, NULL, snake);
	/* :::::WARNING:::::
	 * dragons ahead: the panel functions change the pointing destination of w_game
	 * you have to reset it in main, else you'll spend many hours of debugging not noticing that
	 * all stuff gets written in foreign address space!
	 */
	return w_game;
}
void debug(WINDOW *win, frame *frm, int *xPos, int *yPos){ //FIXME buffer overflow possible
    char *buf = (char*)malloc(100); //WARNING buffer is UNSAFE
    sprintf(buf, "X: %d Y: %d", *xPos, *yPos);
    wmove(win, frm->lines-1, 0); clrtoeol();
    mvwprintw(win, (frm->lines)-1, (frm->cols)-strlen(buf), buf);
    free(buf);
	return;
}
void do_exit(FILE* urandom, int rtn){
    endwin(); //clean up frame
	fclose(urandom);
	exit(rtn);
}