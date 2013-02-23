typedef unsigned char byte;

using namespace std;
#include <iostream>
#include <stdio.h>
#include <string.h>

class Wetterdaten {
  private:
    float temp,humid,airspd;
    int power;
  public:
    byte* toByteArray();
    void fromByteArray(byte*);
    Wetterdaten();
    Wetterdaten(byte*);
    Wetterdaten(float temp, float humid, int power, float airspd);
};

Wetterdaten::Wetterdaten(){}
Wetterdaten::Wetterdaten(float temp, float humid, int power, float airspd){
  this->temp = temp;
  this->humid= humid;
  this->power = power;
  this->airspd = airspd;
}

void Wetterdaten::fromByteArray(byte*){}
byte* Wetterdaten::toByteArray(){
	byte* buf = new byte(16);
	if(!buf){
	   cerr << "allocation error" << endl;
	   return NULL;
	}
	memcpy((void*)buf, (void*)&temp, 4);
	memcpy((void*)buf+4, (void*)&humid, 4);
	memcpy((void*)buf+8, (void*)&power, 4);
	memcpy((void*)buf+12, (void*)&airspd, 4);
	return buf;
}

int main(){
	Wetterdaten w(12.34, 78.9, 956, 30.12);
	byte* b = w.toByteArray();
	for(int i=0; i<16; i++){
      if(i>0) printf(":");
      printf("%02X", b[i]);
	}
	cout << endl;
	return 0;
}
