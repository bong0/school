#include <stdio.h>
#include <unistd.h>
#define MAX 1000
#define SPIELEREI 1

void ReadValue(int *arr, int index);
float MeanValue(int *arr, int index);
int GetMin(int *arr, int index);
int GetMax(int *arr, int index);
#if SPIELEREI>0
void loopLED();
#endif

int main(){
    int n=0, array[MAX];
#if SPIELEREI>0
    printf("\033\[2m"); //set half brightness
    printf("\033\[32m\033\[40m"); //set green foreground & black background
#endif    
    do {
    	printf("Wieviele Messwerte?: ");
    	scanf("%d",&n);
    } while(n<0 || n>=MAX);

    ReadValue(array, n); //CBR array & Anzahl der Messwerte
#if SPIELEREI>0
    printf("\033\[2J"); //clrscr
  //  printf("\033\[7m"); //reverse line
	printf("\033\[5m"); //blink urspruengl. 5m
	printf("\033\[1m");
#endif
    printf("Der Mittelwert der %d Werte ist: %f\n", n, MeanValue(array,n));
	printf("Der minimale Wert ist %d, der maximale %d", GetMin(array,n), GetMax(array,n));
#if SPIELEREI==0
    putchar('\n');
#else
    printf("\033\[m"); //turn off specials 
    loopLED();
    getchar();getchar(); //wait...    
    printf("\033\[2J"); //clrscr
#endif
}

void ReadValue(int *arr, int index){
	for(int i=0; i<index; i++){
		printf("Messwert %d: ",i+1);
		scanf("%d", &arr[i]);
	}
}

float MeanValue(int *arr, int index){
	float meanVal=0.0;
	for(int i=0; i<index; i++){
		meanVal+=arr[i];
	}
	return meanVal/float(index);
}

int GetMin(int *arr, int index){
	int min = arr[0];
	for(int i=1; i<index; i++){
		if(arr[i] < min){
			min = arr[i];
		}
	}
	return min;
}

int GetMax(int *arr, int index){
  int max = arr[0];
	for(int i=1; i<index; i++){
	 if(arr[i] > max){
	   max = arr[i];
	 }
	}
	return max;
}
#if SPIELEREI>0
void loopLED(){
    for(int i=1; i<=3; i++){
        printf("\033\[%dq",i);
        usleep(600);
    }
    for(int i=3; i>=1; i--){
        printf("\033\[%dq",i);
        usleep(600);
    }
}
#endif
