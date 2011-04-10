#include <stdio.h>
#include <ctype.h> // for toupper
#include <ncurses/ncurses.h> //for shell IO
//#include <unistd.h> //for sleep func
//#include <signal.h> //sigint stuff
#include <stdlib.h> //exit()

#define MAXVERSUCHE 10
#define MAXPOS 4

/*
  mastermind.cpp
  MasterMind

  Created by Julian Kessel on 2/25/11.
  GCC 4.2.1
  This program is free software; you can redistribute it and/or 
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
  */

//void sigintcallback();
int main() {
//INIT stuff
initscr();
raw();
noecho();
timeout(-1); //turn off blocking
//signal(SIGINT, &sigintcallback);

char vorgabe[MAXPOS];
char versuch[MAXPOS]; //jede Eingabe
char getroffen[MAXPOS]; //getroffene Buchstaben
int schwarz, weiss; //zaehler fuer getroffene buchstaben

printw("Bitte geben sie ihre zu ratende Kombination ein (B,G,Y,O,R,M): ");

for(int i=0;i<MAXPOS; i++){ //lese Vorgabe ein
    char buf;
    do {
        buf = toupper(getch());
    }
    while(buf<=MAXPOS+1);
	vorgabe[i] = buf;
	printw("_%c_", vorgabe[i]);
}
refresh(); //update screen
//sleep(1); //zur kontrolle
clear(); //clear screen

for(int v=0;v<=MAXVERSUCHE;v++){
    for(int a=0;a<MAXPOS;a++) getroffen[a] = vorgabe[a]; //Wert kopieren
    
    if(v==MAXVERSUCHE){
        printw("Pech! Die richtige Kombination lautet: _");
        for(int i=0;i<MAXPOS;i++){
            printw("_%c_", vorgabe[i]);
        }
        putchar('_');
        break;
    }
    else if(schwarz==MAXPOS){
        printw("Gratulation! Geraten nach %d Versuchen.", v);
        break;
    }
    schwarz=0; weiss=0; //clear variables
    
    printw("%d. Versuch: ", v+1);
    
    //gehe in Abfrageschleife
    for(int i=0;i<MAXPOS; i++){ //lese Versuch ein
    	versuch[i] = toupper(getch());
    	printw("_%c_", versuch[i]);
    }

    //vergleiche Versuch mit Vorgabe
    for(int vindex=0;vindex<MAXPOS; vindex++){ //gehe durch getroffen und versuch; index ist der einzelne char
        if(versuch[vindex] == getroffen[vindex]){
            schwarz++; //richtiger Char an richtiger Stelle
            getroffen[vindex] = 0; //markieren
        }
        else{ //suche nun für den aktuellen index in versuch einen gleichen in getroffen
            bool isDuplicate = false;
            bool occuredOnce = false;
            
            for(int gindex=0;gindex<MAXPOS;gindex++){ //gehe durch getroffen und suche nach uebereinstmmungen zum aktuellen vindex
                if(getroffen[gindex] == versuch[vindex]){
                    for(int gr=0;gr<MAXPOS;gr++){
                        if(getroffen[gr] == vindex){
                            if(!occuredOnce) occuredOnce = true;
                            else isDuplicate = true;
                        }
                    }
                    if(!isDuplicate) weiss++; //irgendwo ein richtiger Char
                    versuch[vindex] = gindex+1; //markieren
                }
            }
        }
    }
    printw("\t|| Schwarz: %d\t Weiss: %d\n", schwarz, weiss);
}

getch();
//printf("\e[2J\e[H"); //clrscr
endwin();
return 0;
}

/*void sigintcallback(){
    endwin();
    exit(1);
}*/