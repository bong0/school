/*
 * declarations included by main.cpp of the snake project
 */

#define MAX_X 80
#define MAX_Y 25

typedef struct { //store common properties of a frame
	int lines;
	int cols; // columns
	int centerX;
	int centerY;
} frame;
typedef struct { //describes a chacacter drawn on screen (snake body, cookie etc.)
    int xPos;
    int yPos;
} character;
typedef struct {
    int body[2][MAX_X*MAX_Y]; //x y
	int lastPos_h[2]; //last position of head x y
	int lastPos_t[2]; //last position of tail x y
	int headsym;
    int bodysym;
    int length;
} snake;

bool chdir_snake(WINDOW *w_game, frame *term, int *xPos, int *yPos, char *vector, snake *snk, bool *vec_diff);
void draw_snake(WINDOW *w_game, snake *snake);
bool mv_snake(WINDOW *w_game, frame *game, frame *term, snake *snake, int *xPos, int *yPos, char vector[], int cookie[], FILE *urandom, bool vec_diff);
WINDOW* prep_game(WINDOW *w_game, WINDOW *w_gamefrm, PANEL *p_game, PANEL *p_gamefrm, frame *game, frame *term, int *xPos, int *yPos, snake *snake);
void setup_term(frame *term, WINDOW *w_game);
void wait(char *vector, float *speed);
void do_refresh(WINDOW *w_game, int *xPos, int *yPos, char *vector, snake *snake);
bool outOfBounds(int *xPos, int *yPos, frame *frm_game); //is that pos out of frm bounds?
void hitFrame(frame *frm, FILE *urandom); //callback when frame was hit
void placeCookie(WINDOW *win, frame *frm, int* cookie, FILE *urandom);
void draw_stats(frame *frm, FILE *urandom);
void draw_border(WINDOW *win);
void ask_quit(WINDOW *win, frame *frm); //ask wheter user wants to exit
void do_exit(FILE* urandom, int rtn=0);
/* debugging functions */
void debug(WINDOW *win, frame *frm, int *xPos, int *yPos);
void inputStatus(WINDOW *win, frame *frm, bool idle);
void print_arr(WINDOW *win, snake *snk, int len);