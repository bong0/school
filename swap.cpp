#include <stdio.h>

bool swap(float *a, float *b);
float maxVal(float var1, float var2);

int main(){
 float x,y;
 printf("Geben sie einen Wert x ein: "); scanf("%f", &x);
 printf("Geben sie einen Wert y ein: "); scanf("%f", &y);
 printf("Swap returned: %d\n", swap(&x,&y));
 printf("Swapped| x:%f y:%f\n", x,y);
 printf("Groessere der beiden Werte: %f\n", maxVal(x,y));
}

//Aufgabe 4.1
bool swap(float *a, float *b){
 float buf;
 buf = *b;
 *b = *a;
 *a = buf;
 return ((*a == *b)? 1:0);
}

float maxVal(float var1, float var2){
 return((var1>=var2) ? var1:var2);
}
