#include <stdio.h>
/* a small exercise to understand passing command line arguments and interpret them */

int main(int argc, const char *argv[]){
 int ec=0;
	for(int i=1; i<argc; i++){
		for(int b=0; argv[i][b]!=0; b++){
			if(argv[i][b] == 'e') ec++;
		}
	}
	printf("es: %d\n",ec);
}
