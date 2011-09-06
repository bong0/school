#include <iostream>
#include <sstream>
#include <math.h>
#include "Vektor.h"


Vektor::Vektor(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vektor::Vektor(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
//initialisierungsliste blabla:this->x(x)
}

std::string Vektor::show(){
    std::stringstream stream; 
    stream << "(" << this->x << "|"
                  << this->y << "|"
                  << this->z << ")";
    return stream.str();
}

Vektor Vektor::vadd(Vektor v1){
    return Vektor (
        this->x + v1.x,
        this->y + v1.y,
        this->z + v1.z
    );
}

double Vektor::Betrag(){
    return sqrt(
            (this->x)*(this->x)+
            (this->y)*(this->y)+
            (this->z)*(this->z)
    );
}

double Vektor::getX(){
    return this->x;
}
double Vektor::getY(){
    return this->y;
}
double Vektor::getZ(){
    return this->z;
}
void Vektor::setX(double x){
    this->x = x;
}
void Vektor::setY(double y){
    this->y = y;
}
void Vektor::setZ(double z){
    this->z = z;
}
Vektor Vektor::operator+(Vektor v1){
    return this->vadd(v1);
}
double Vektor::operator+(double f){
    return this->Betrag()+f;
}

Vektor::~Vektor() {
    std::cout << "gelöscht." << std::endl;
}
