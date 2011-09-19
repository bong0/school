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
    /* auch möglich:
     * return Vektor(x+v1.x, y+v1.y, z+v1.z);
     */
}
double Vektor::operator+(double f){
    return this->Betrag()+f;
}

/* _Wieso_ funktioniert das nicht?
 * std::ostream& Vektor::operator<<(std::ostream &ostr){
    ostr << "(" << this->x
         << "|" << this->y
         << "|" << this->z
         << ")";
    return ostr;
 */

Vektor::~Vektor() {
    std::cout << "gelöscht." << std::endl;
}

std::ostream& operator<<(std::ostream &ostr, Vektor &v1){
    ostr << "(" << v1.x
         << "|" << v1.y
         << "|" << v1.z
         << ")";
    return ostr; 
}

std::istream& operator>>(std::istream &istr, Vektor &v1){
    std::cout << "x: ";
    istr >> v1.x;
    std::cout << "y: ";
    istr >> v1.y;
    std::cout<< "z: ";
    istr >> v1.z;
    return istr; 
}