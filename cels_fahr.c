#include <stdio.h>

int main(){
	float lower, upper, step;

	printf("Startwert: ");
	scanf("%f", &lower);
	printf("Endwert: ");
	scanf("%f", &upper);
	printf("Schrittweite: ");
	scanf("%f", &step);
	
	printf("Eingabeeinheit [C/F]: ");
	switch (getchar(),getchar()) {
		case 'C':
		case 'c':
			printf("Celsius\t|\tFahrenheit\n");
			for(;lower<=upper;lower+=step){
				printf("%f\t|\t%f\n", lower, lower*(9.0/5.0)+32);
			}
			break;
		case 'F':
		case 'f':
			printf("Fahrenheit\t|\tCelsius\n");
			for(;lower<=upper;lower+=step){
				printf("%f\t|\t%f\n", lower, (lower-32)*(5.0/9.0) );
			}
			break;
			
		default:
			printf("\nEingabefehler!\n");
			break;
	}
	
	return 0;
}