#include <stdio.h>
#include <string.h>
#include <ctype.h>

int myatoi(char *str);
//multi mit 10 und add

int main(){
char str1[50];
 printf("Bitte geben Sie Ziffern ein: "); gets(str1);
 
 printf("atoi returned %d\n", myatoi(str1));

 return(0);
}

int myatoi(char *str){
	int retVal=0;
	int sign=1;
	
	for(int i=0; *str!=0 && i<strlen(str); i++){
		if(!(*str>='0' && *str<='9') && *str !='+' && *str !='-') return 0;
		if(*str == '-') sign=-1;
		retVal = (retVal*10)+(str[i]-'0');
		printf("IT=%d, val=%d\n", i,retVal);
	}
	return retVal*sign;
}

