#include <stdio.h>

double fac(long int n);
double fac_it(int n);

int main(){
	int inp = 0;
	double erg = 0;
	printf("Berechne Fakultaet von: "); scanf("%ld", &inp);
	erg = fac_it(inp);
	printf("Fakultaet (exp): %e\n", erg);
    printf("Fakultaet (fp): %lf\n", erg);

	return 0;
}
double fac(long int n){
	return (n?n*fac(n-1):1);
}
double fac_it(int n){
    double fac = 1;
    for(; n>0; n--){
        fac*=n;
    }
    return fac;
}
