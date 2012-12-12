#include <iostream>
#include <conio.h>

#include "Serial.h"

/*
 * A simple serial echo client on 9600 8N1
 * handshaking is omitted
 * *uses some serial wrapper class by a teacher of my school, sorry*
 * - Julian Kessel 2012
 */

using namespace std;

int main(){
  Serial* serial = new Serial("COM1",
							  9600, //baudrate
							  8, //data bits
							  1, //stop bits
							  1 //parity
  );

  if(!serial.open()){
	cout << "Error opening serial port! exiting..." << endl;
	exit(1);
  }
//serial.setDTR(true);

  cout << "This echoclient is completely passive, any input will make me quit." << endl;
  
  while(!kbhit()){
	int ccount = serial.dataAvailable();
	int* buf = new int[ccount];
	if(buf==NULL){
	  cout << "Could not allocate enough amount of memory for efficient processing! Falling back to bytewise-mode..." << endl;
	  int chr = serial.read();
	  if(chr != -1){
		serial.write(toupper(chr));
		continue;
	  }
	  cout << "Waiiit... we seem to have some other problem here, I cannot read from the serial interface :/ ciao" << endl;
	  exit(1);
	}
	
	if(serial.read(buf, ccount) != -1){
	  for(int i=0, i < ccount; i++){
		buf[i] = toupper(buf[i]);
	  }
	  serial.write(buf, ccount);
	}
	delete [] buf;
  }

  serial.close();
  
  exit 0;
}
