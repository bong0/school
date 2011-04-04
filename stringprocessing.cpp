#include <stdio.h>
#include <iostream>
#include <stdlib.h> //for malloc

using namespace std;
#define MALLOC 1
#define COUNT_DEMO 1

int mystrlen(char *str, int processType);
bool mystrcpy(char *src, char *dst);
bool mystrcat(char *src, char *dst);
bool dynRead(char *inpArr);
void mystrrev(char *str);
void outOfMem();

int main(){

    char *inpArr1 = (char*)malloc(sizeof(char));  //semi-dynamic array, expanding :)
    char *inpArr2 = (char*)malloc(sizeof(char));  //semi-dynamic array, expanding :)

    if(inpArr1 == NULL || inpArr2 == NULL) outOfMem();
    
    dynRead(inpArr1);
    dynRead(inpArr2);
    printf("Die Laenge des vorderen Strings \"%s\" ist: %d.\n", inpArr1, mystrlen(inpArr1, 2));
    printf("Die Laenge des hinteren Strings \"%s\" ist: %d.\n", inpArr2, mystrlen(inpArr2, 2));
    
    char* tmp = inpArr2;
    while(*tmp++){ // run until 
        if(inpArrr1==NULL)outOfMem(); //catch exception
        inpArr1 = (char*)realloc((void*)inpArr1, sizeof(char)); //expand 1B too large
    }
    mystrcat(inpArr2,inpArr1); //cat strings, arr2 in arr1
    
    mystrrev(inpArr1); //reverse catted str
    printf("%s\n", inpArr1); //print reversed, concatenated string

//free up mem
free(inpArr1);
free(inpArr2);

return 0;
}

bool dynRead(char *inpArr){
    char tmpChar;
    
    printf("Bitte geben sie einen String ein: ");
    
    //the second condition is because we can't count indexes above the addrspace of (u)int
    unsigned int i;
    for(i=0; ((tmpChar=getchar()) != '\n'); i++){
        if(i >= (2<<(sizeof(int)*8)-1)-1){ //val range of uint
            printf("\nnoooo, that's too long\n");
            break;
        }
        else if(i==0){
            *inpArr = tmpChar; //write to first index
        }
        else{
            inpArr = (char*)realloc((void*)inpArr, sizeof(char)); //inflate array, and reassing it, could have moved 
            if(inpArr == NULL) outOfMem(); //catch exception
            char *addr = &inpArr[i]; //inflate inpArr
            *addr = tmpChar; //write to following index
        }
    }
  //  inpArr = (char*)realloc((void*)inpArr, sizeof(char));
  //  inpArr[i+1] = 0;
    return 0;
}
int mystrlen(char *str, int processType){
    int charCount=0;
    switch(processType){
        case 1:
            for(int i=0; str[i]!='\0';i++){
                charCount++;
            }
            break;
        case 2:
            for(int i=0; *(str+i)!='\0';i++){
                charCount++;
            }
            break;
        case 3:
            for(int i=0; *str++!='\0';i++){
                charCount++;
            }
            break;
    }
    return charCount;
}

bool mystrcpy(char *src, char *dst){
 while(*src) *dst++ = *src++;
 return 0;
}

bool mystrcat(char *src, char *dst){
    if(*dst) while(*++dst); //jump to end of array if not a single char array
    while(*src) *dst++ = *src++; //fill indexes of dst with src chars
    *++src=0; // set termination
 return 0; // successful :P ,hopefully
}

void mystrrev(char *str){
    char *rp=str,buf;
    if(*rp) while(*++rp);
    
    while(rp>=str){
        if(!(*rp)) rp--; //if on \0
        buf = *rp; //cache last 
        *rp = *str; //
        *str = buf; //replace front index val with back index'
        rp--; //go further
        str++;
    }
    return;
}

void outOfMem(){
    printf("FATAL: Out of Memory\n");
    exit(1);
}
