#include <iostream>
#include <cstdlib>
#include "T.h"

using namespace std;

T::T(){
 this->arr = new int[10];
 this->arrLength = 10;
 if(!(this->arr)) outofmem();
 for(int i=0; i<10; i++){
  arr[i] = i*10;
 }
}

T::T(int src[], int length){
    this->arr = new int[length];
    this->arrLength = length;
    if(arr==NULL)outofmem();
    for(; length>0; length--){
        (this->arr)[length-1] = src[length-1];
    }
}
T::T(T& orig){ // Copy-Konstruktor | and since GCC 4.6.2 _still_ doesn't support delegating constructors, we have redundant code
    this->arr = new int[orig.length()];
    this->arrLength = orig.length();
    if(arr==NULL)outofmem();
    for(int i=0; i<arrLength; i++){
        (this->arr)[i] = orig.arr[i];
    }    
}

int T::length(){
    return this->arrLength;
}
void T::print(){
 for(int i=0; i<arrLength; i++){
  cout << "item " << i << ": " << (this->arr)[i] << endl;
 }
}
int T::betrag(){
    int betrag = 0;
    for(int i=0; i<sizeof(arr); i++){
        betrag+=arr[i];
    }
    return betrag;
}
T::operator int(){return this->betrag();}

T& T::operator=(T& obj){
    if(&obj == this) return *this; //catch a = a cases 
    if(arr != NULL) delete [] arr; //wipe old data
    this->arr = new int[obj.length()]; //get length of src obj's array & get mem of that size
    if(this->arr == NULL) outofmem();
    for(int i=0; i<obj.length(); i++){ //copy over values
        this->arr[i] = obj.arr[i];
    }
    return *this;
}
void T::outofmem(){
    cout << "out of mem!" << endl;
    exit(1);
}
T::~T(){
 cout << "died" << endl;
 delete [] arr;
}

int operator+(int l, T& obj){
    return (l+=obj.betrag());
}