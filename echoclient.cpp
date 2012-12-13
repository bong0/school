#include <iostream>
#include <conio.h>

#include "Serial.h"
/*
 * A simple serial echo client on 9600 8N1
 * handshaking is done via ETX/ACK
 * *uses some serial wrapper class by a teacher of my school, sorry*
 * - Julian Kessel 2012
 */

using namespace std;

//void waitForReceiver(Serial* serial);

int main(){
  Serial* serial = new Serial("COM1",
							  9600, //baudrate
							  8, //data bits
							  ONESTOPBIT, //stop bits
							  NOPARITY //parity
  );

  if(!serial->open()){
	cout << "Error opening serial port! exiting..." << endl;
	exit(1);
  }

  //waitForReceiver(serial);

  cout << "This echoclient is completely passive, any input will make me quit." << endl;
  
  while(!_kbhit()){
	int ccount = serial->dataAvailable();
	if(ccount<=0) continue;
	char* buf = new char[ccount+1];
	buf[ccount]='\0';

	if(buf==NULL){
	  cout << "Could not allocate enough amount of memory for efficient processing! Falling back to bytewise-mode..." << endl;
	  int chr = serial->read();
	  if(chr != -1){
		serial->write(toupper(chr));
		 //serial->write(0x03); // send ETX
		 //waitForReceiver(serial);
		continue;
	  }
	  cout << "Waiiit... we seem to have some other problem here, I cannot read from the serial interface :/ ciao" << endl;
	  exit(1);
	}
	
	cout << "reading..." << endl;
	if(serial->read(buf, ccount) != -1){
	  for(int i=0; i < ccount; i++){
		cout << "converting to upper" << endl;
		buf[i] = toupper(buf[i]);
	  }
	  printf("writing %s to other end\n", buf);
	  serial->write(buf, ccount);
	  //serial->write(0x03); // send ETX
	  //waitForReceiver(serial);
	}
	delete [] buf;
  }

  serial->close();
  
  exit(0);
}

/*
void waitForReceiver(Serial* serial){
  while(true){
	if(serial->isDSR()) break;
	cout << "Waiting for DTR on receiver is HIGH (DSR on svr)" << endl;
	Sleep(100);
 }
 while(true){
	if(serial->read()==0x06) break;
	cout << "Waiting for ACK from receiver" << endl;
	Sleep(100);
 }
}*/
