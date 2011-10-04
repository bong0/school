/* 
 * File:   KennlinienAblage.cpp
 * Author: bongo
 * 
 * Created on September 22, 2011, 10:38 AM
 */

#include "KennlinienAblage.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#define U_POS 0
#define I_POS 1
using namespace std;

KennlinienAblage::KennlinienAblage(int anzahl) {
    try {
        this->parr = new float[anzahl][2]; // liefert float** !
    }
    catch(bad_alloc){ 
        cout << "BAD ALLOC - TERMINATING" << endl;
        exit(1);
    }
    this->anzahl = anzahl;
}

void KennlinienAblage::init(int anzahl, float parr[][2]){
    delete [] this->parr;
    try {
        this->parr = new float[anzahl][2];
    }
    catch(bad_alloc){ 
        cout << "BAD ALLOC - TERMINATING" << endl;
        exit(1);
    }
    for(int i=0; i<anzahl; i++){
        (this->parr)[i][U_POS] = parr[i][U_POS];
        (this->parr)[i][I_POS] = parr[i][I_POS];
    }
    this->anzahl = anzahl;
}

KennlinienAblage::KennlinienAblage(int anzahl, float parr[][2]) {
    this->init(anzahl, parr);
}

KennlinienAblage::KennlinienAblage(const KennlinienAblage& orig){ // Copy-Konstruktor
    this->init(orig.anzahl, orig.parr);
}

KennlinienAblage& KennlinienAblage::operator=(const KennlinienAblage& orig){ // Überladener ZuweisungsOP
    // prüfe ob Quelle = Ziel
    if(this != &orig){
        this->init(orig.anzahl, orig.parr);
    }
    return *this;
}

float KennlinienAblage::getI(float u){
    int index = binSearch(0,this->anzahl, u, U_POS); // search for corresponding U value
    
    if(index >= 0)
       return (this->parr)[index][I_POS];
}

float KennlinienAblage::getU(float i){
    int index = binSearch(0,this->anzahl, i, I_POS); // search for corresponding I value
    if(index >= 0){
        return (this->parr)[index][U_POS]; // return U value on found pos
    }
}

bool KennlinienAblage::setData(){
    cout << "Bitte geben sie Punkte der Kennlinie ein: " << endl;
    for(int i=0; i < this->anzahl; i++){
        cout << "U: ";
        cin >> (this->parr)[i][U_POS];
        cout << "\033[2K\rI: ";
        cin >> (this->parr)[i][I_POS];
        cout << "\r" << (this->parr)[i][U_POS]
             << "\t"
                     << (this->parr)[i][I_POS]
            << endl;
    }
}

void KennlinienAblage::show(){
    if(this->anzahl<1)
        cout << "ERROR" << endl;
    
    cout << "Kennlinien-Listing:" << endl
         << "   U\t\tI" << endl;
    for(int i=0; i<this->anzahl; i++){
        cout << i+1 << ": " << (this->parr)[i][U_POS]
                    << "\t\t" << (this->parr)[i][I_POS]
             << endl;  
    }
}

KennlinienAblage::~KennlinienAblage() {
    delete [] parr;
}

int KennlinienAblage::binSearch(int lb, int rb, float key, int search_line){
    if(rb<lb || lb >rb)
        return (numeric_limits<float>::min()); //anchor
    int cntr = lb+((rb-lb)/2); // calc center

    if((this->parr)[cntr][search_line] == key) return cntr; // we've found it
    else
        if((this->parr)[cntr][search_line] > key)
            rb = cntr-1;
    else
        lb = cntr+1;
    return this->binSearch(lb, rb, key, search_line);
}
