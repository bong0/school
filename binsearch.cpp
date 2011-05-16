#include <stdio.h>

int binsearch(int *arr, int lb, int rb, int key); //the recursing version
int binsearch_it(int *arr, int lb, int rb, int key); //the iterative version
int main(){
    int arr[30];
    int key=0;
    for(int i=1; (i*3)<=60 && i<=30; i++) arr[i] = i*3;
    
    do printf("Schlagen sie ein Vielfaches von 3 im Bereich 0-60 vor: ");
    while( (scanf("%d", &key),key)%3 );
    
    printf("%d\n", binsearch_it(arr, 0, 30, key));
return 0;
}

int binsearch(int *arr, int lb, int rb, int key){
    if(rb<lb || lb >rb) return -1; //anchor
    int cntr = lb+((rb-lb)/2); // calc center
    printf("CNTR:%d | LB:%d | RB:%d\n", arr[cntr], lb, rb);

    if(arr[cntr] == key) return cntr; // we've found it
    else
        if(arr[cntr] > key)
            rb = cntr-1;
    else
        lb = cntr+1;
    return binsearch(arr, lb, rb, key);
}
int binsearch_it(int *arr, int lb, int rb, int key){
    int cntr=0;
    int data_length = rb;
    for(int i=0; i<=data_length; i++){
        cntr = lb+((rb-lb)/2);
        printf("CNTR:%d | LB:%d | RB:%d\n", arr[cntr], lb, rb);
        
        if(arr[cntr] == key) return cntr; // we've found it
        else
            if(arr[cntr] > key)
                rb = cntr-1;
        else
            lb = cntr+1;
    }
    return -1; //we weren't successful :(
}
