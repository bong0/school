/* 
 * File:   Fan.cpp
 * Author: bongo
 * 
 * Created on September 7, 2011, 6:11 PM
 */

#include "Fan.h"

Fan::Fan(std::string fan_model, long rotation_speed,
         bool hooligan):fan_model("Aggressor"),rotation_speed(9999),
                        hooligan(true)  // Eine Initialisierungsliste
{
    
    this->fan_model = fan_model             //Einige this->pointer
    this->rotation_speed = rotation_speed;
    this->hooligan = hooligan;
}

Fan::Fan(const Fan& orig) {
    
}

void Fan::print(){
    std::cout << "Hallo, Ich bin " << (hooligan)?"":"k" << "ein" << "Hooligan" << std::endl
              << "Modell: " << fan_model
              << " Rotationsgeschw.: " << rotation_speed << std::endl;
           
}
Fan::~Fan() {
    std::cout << "It was one of us who died..." << std::endl;
}

