#include <iostream>
#include <stdio.h>

int main () {
	char pport; // Schieberegister: steuert u.a. die Pumpen
				// bit0 : Solarpumpe
				// bit1 : Heizpumpe
				// Zustand 1: an 0: aus
	char fortfahren;
	float vtemp; // Vorlauftemperatur Solarkollektor
	float btemp; // Brauchwassertemperatur
	
	do {
		printf("Vorlauftemperatur: ");
			scanf("%f", &vtemp);
		printf("Brauchwassertemperatur: ");
			scanf("%f", &btemp);
		
		if (btemp<36) {
			pport&=0x0; //Solarpumpe aus 
			pport|=0x1; //Heizpumpe ein
		}
		else if(vtemp>=(btemp+5)) {
			pport|=0x1; //Solarpumpe ein
			pport&=0x0; //Heizpumpe aus
		}
		else { 
			pport&=0x0; //Solarpumpe aus 
		}

		printf("Status Solarpumpe: %s\n", (pport<<7)>>7?"an":"aus");
		printf("Status Heizpumpe: %s\n", (pport<<6)>>8?"an":"aus");
		printf("pport: %08x\n", pport);
		
		printf("\nMöchten sie das Programm beenden[J/N]? ");
		fflush(stdin);
		scanf(" %c", &fortfahren);
	} while (fortfahren!='J'&&fortfahren!='j');
    return 0;
}
