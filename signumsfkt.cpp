#include <stdio.h>
/* Erstelle je ein Struktogramm und Programmstück zur Realisierung der Signumsfkt. */
int signum(int x);
int betrag(int x);
int main(){
	int x,y;	
	printf("Eine Zahl eingeben: ");
	scanf("%d", &x);
	y = signum(x);
	printf("Signum: %d\n", y);
	x = betrag(x);
	printf("Betrag: %d\n", x);
}

int signum(int x){
	if(x<0){
		x=-1;
	}
	else if(x!=0){
		x=1;
	}
	return x;
}

int betrag(int x){
	if(x<0) return x=-x;
	else return x;
}