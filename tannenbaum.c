#include <stdio.h>

int genpx(char pxccount, char character, bool lf);

int main () {
	//spx: star pixel | epx: empty pixel
	char spx, epx;
	for (spx=0,epx=61; spx<=61; spx++,epx--) {
		genpx(epx/2, ' ', 0);
		genpx(spx, '*', 0);
		genpx(epx/2, ' ', 1);
	}
	for (char stamm=1; stamm<=10; stamm++) {
		genpx((61/2)-5, ' ', 0);
		genpx(10, '*', 0);
		genpx((61/2)-5, ' ', 1);

	}
    return 0;
}

int genpx(char pxccount, char character, bool lf){
	for (char i=0; i<=pxccount; i++) {
		printf("%c", character);
	}
	if (lf) {
		printf("\n");
	}
	return 0;
}
