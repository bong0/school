#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#define uint unsigned int

typedef struct {
	//address octets
	unsigned int oct1;
	unsigned int oct2;
	unsigned int oct3;
	unsigned int oct4;
	//whole addr/mask
	unsigned int *addr;
	unsigned int *mask;
	//id
	unsigned int id;
} ipv4;

int checkaddr(uint oct1, uint oct2, uint oct3, uint oct4){
	uint* octs[4] = { &oct1, &oct2, &oct3, &oct4 };

	for (int count=0; count<4; count++) {
		if (*octs[count] > 255 || *octs[count] < 0) {
			printf("[-] Input error in octet %i\n", count+1);
			return 1;
		}
	}
	return 0;
}

int main(){
	
	ipv4 host, net;
	host.addr = (unsigned int *)malloc(sizeof(unsigned int));
	net.mask = (unsigned int *)malloc(sizeof(unsigned int));

  //Host Adresse einlesen	
	printf("Bitte die IP-Addr. eingeben: ");
	scanf("%03u.%03u.%03u.%03u",	&host.oct1,
							&host.oct2,
							&host.oct3,
							&host.oct4);
	if(checkaddr(host.oct1,host.oct2,host.oct3,host.oct4)){return 1;}
	*host.addr = (host.oct1<<24) + (host.oct2<<16) + (host.oct3<<8) + (host.oct4);
	
  //Subnetzmaske einlesen
	fflush(stdin);
	printf("Bitte die Subnetzmaske eingeben: ");
	scanf("%03u.%03u.%03u.%03u",  &net.oct1,
						  &net.oct2,
						  &net.oct3,
						  &net.oct4);
	if(checkaddr(net.oct1,net.oct2,net.oct3,net.oct4)){return 1;}
	*net.mask = (net.oct1<<24) + (net.oct2<<16) + (net.oct3<<8) + (net.oct4);
  
//Host Addr maskieren	
	net.id = *host.addr & *net.mask;
	host.id = *host.addr & ~(*net.mask);
	printf("\nHost ID: 0x%08x\n", host.id);
	printf("Net ID: 0x%08x\n", net.id);
	
	printf("Host ID: %u.%u.%u.%u\n",	((host.id)>>24),
							((host.id)<<8)>>24,
							((host.id)<<16)>>24,
							((host.id)<<24)>>24);
	
	printf("Net ID: %u.%u.%u.%u\n",	(net.id)>>24,
							(net.id<<8)>>24,
							(net.id<<16)>>24,
							(net.id<<24)>>24);
		
	free(host.addr);
	free(net.mask);
	return 0;
}
