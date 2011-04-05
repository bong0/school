#include <stdio.h>
#include <stdlib.h> //for malloc

int mystrlen(char *str, int processType);
bool mystrcpy(char *src, char *dst);
bool mystrcat(char *src, char *dst);
int dynRead(char *inpArr); //returns 'true' length e.g. w/ \0
void mystrrev(char *str);
void outOfMem();
void alloced(unsigned int bytes, bool truncate=0); //for debugging purposes

int main(){

    char *inpArr1 = (char*)malloc(sizeof(char));  //semi-dynamic array, expanding :)
    char *inpArr2 = (char*)malloc(sizeof(char));  //semi-dynamic array, expanding :)

    if(inpArr1 == NULL || inpArr2 == NULL) outOfMem();
    
    printf("arr1 has grown to %d bytes\n",dynRead(inpArr1));
    //alloced(0,1); putchar('\n');
    printf("arr2 has grown to %d bytes\n",dynRead(inpArr2));
    //alloced(0,1); putchar('\n');
    printf("Die Laenge des vorderen Strings \"%s\" ist: %d.\n", inpArr1, mystrlen(inpArr1, 1));
    printf("Die Laenge des hinteren Strings \"%s\" ist: %d.\n", inpArr2, mystrlen(inpArr2, 1));

    char* tmp = inpArr2;
    while(*tmp++){ // run until
        if(inpArr1==NULL)outOfMem(); //catch exception
        inpArr1 = (char*)realloc((void*)inpArr1, sizeof(char)); //expand 1B too large
    }
    mystrcat(inpArr2,inpArr1); //cat strings, arr2 in arr1
    
    mystrrev(inpArr1); //reverse catted str
    printf("%s\n", inpArr1); //print reversed, concatenated string


//free up mem FIXME
free(inpArr1);
free(inpArr2);

return 0;
}

int dynRead(char *inpArr){
    char tmpChar;
    
    printf("Bitte geben sie einen String ein: ");
    
    //the second condition is because we can't count indexes above the addrspace of (u)int
    unsigned int i; //needed for termination char
    for(i=0; ((tmpChar=getchar()) != '\n'); i++){
        if(0/*i >= (2<<(sizeof(int)*8)-1)-1*/){ //val range of uint
            printf("\nnoooo, that's too long\n");
            exit(1);
        }
        else if(i==0){
            *inpArr = tmpChar; //write to first index
        }
        else{
            //inflate array, and reassing it, could have moved, +1 because we have to count index 0
            inpArr = (char*)realloc((void*)inpArr, sizeof(char)*(i+1)); 
            if(inpArr == NULL) outOfMem(); //catch exception
            inpArr[i] = tmpChar; //write to created index
        }
    }

    i++; //we grow
    inpArr = (char*)realloc((void*)inpArr, sizeof(char)*(i+1)); // alloc 1 more
    inpArr[i] = '\0'; //set nullbyte

    return i++; //include index 0
}
int mystrlen(char *str, int processType){
    int cc;
    switch(processType){
        case 1:
            for(cc=0; str[cc]!='\0';cc++){
                cc++;
            }
            break;
        case 2:
            for(cc=0; *(str+cc)!='\0';cc++){
                cc++;
            }
            break;
        case 3:
            for(cc=0; *str++!='\0';cc++){
                cc++;
            }
            break;
    }
    return cc;
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
void alloced(unsigned int bytes, bool truncate){
    static unsigned int bytecount;
    if(truncate){ bytecount=0; return; }
    bytecount+=bytes;
    printf("\rallocated %u bytes", bytecount);
}
