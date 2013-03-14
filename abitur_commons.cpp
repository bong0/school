/* 
 * A quick demo on some stuff you need in the Abitur
 * to save space and having to write too much, a compressed
 * with inline code is used.
 *
 * DO NOT FORGET:
 *  - to implement a default constructor: there is no nullifying const. in C++
 *  - do not use umlauts and such.
 *  - a replacement for ArrayList in Java is vector, probably list not so much
 *    because it doesn't implement random access.
 */
#include <string>
#include <vector>
using namespace std;
#pragma once
#define uint unsigned int

class Pruefstand {
	  public:
        Pruefstand(){}
};

class Kunde {
	private:
		uint id;
		string name, plz, ort;
		vector<Pruefstand*> pfst;
	public:
		Kunde(){id=0;name=plz=ort="";}
		Kunde(uint id, string name, string plz, string ort){
			this->id = id;
			this->name = name;
			this->plz = plz;
			this->ort = ort;
		}
		uint getId() const {return id;}
		string getName() const {return name;}
		string getPlz() const {return plz;}
		string getOrt() const {return ort;}
		void setOrt( string ort ){this->ort = ort;}
		
		void addPruefstand(Pruefstand *p){pfst.push_back(p);}
		Pruefstand* getPruefstand(int i){
			if(i<0 || i>=pfst.size()){ return NULL; }
			return pfst[i];
		}
};

