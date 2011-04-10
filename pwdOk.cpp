#include <stdio.h>
#include <string.h>
#include <ctype.h>


int pwdOk(char *pwd, char *rule);

int main(){
    char str1[50];
    char rule[]="AAZZZA"; // Z - Ziffer A - Buchstabe
     printf("Bitte geben Sie ein %d Zeichen langes \"Passwort\" ein: ", (int)strlen(rule));
        scanf("%s", str1);
     printf("pwdOk returned %d\n", pwdOk(str1, rule));

    	return 0;
}
int pwdOk(char *pwd, char *rule){
    	unsigned short int pwdOk=0; 
    	if(strlen(rule)!=strlen(pwd)) return -1; // invalid lengths
    	for(int i=0; i<=strlen(pwd); i++){
    		switch(rule[i]){
    			case 'A':
    				if(isalpha(pwd[i])) pwdOk+=1;
    				break;
    			case 'Z':
    				if(isdigit(pwd[i])) pwdOk+=1;
    				break;
    		}
    	}
        return (pwdOk==6)?1:0; //if all six chars match the pattern, the counter should equal 6
}
