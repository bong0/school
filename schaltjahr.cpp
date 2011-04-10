#include <stdio.h>
/* Schreibe ein Programm, das entscheidet, ob ein gegebenes Jahr ein Schaltjahr ist oder nicht.
   Schaltjahr-Kriterien :  - das Jahr ist durch 4 teilbar und nicht durch 100 teilbar.  
   oder    - das Jahr ist durch 4 teilbar , durch 100 teilbar und durch 400 teilbar.
*/

int main(){
	int inp;
	char str[2];
	
	printf("Eingabe Jahr: ");
	scanf("%4d", &inp);
	
	if( !(inp%4) && !(inp%100) ){
	  printf("Das gegebene Jahr ist ein Schaltjahr\n", str);
	  if( !(inp%400) ){
	    printf("Das gegebene Jahr ist ein Schaltjahr\n", str);
	  }
	}
	else{
		printf("Das gegebene Jahr ist kein Schaltjahr\n", str);
	}

}
