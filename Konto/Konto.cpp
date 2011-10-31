/* 
 * File:   Konto.cpp
 * Author: bongo
 * 
 * Created on August 16, 2011, 9:27 PM
 */

#include <string>
#include <string.h>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h> 
#include "Konto.h"

Konto::Konto() {
    this->ktonr = 0;
    this->ktostand = 0; // Startguthaben
    this->pin = "12345";
    this->inhaber = "Anonymous";
    this->isAuthorized = false;
}
Konto::Konto(uint ktonr, double ktostand, std::string inhaber, std::string pin){
    this->ktonr = ktonr;
    this->ktostand = ktostand;
    this->inhaber = inhaber;
    this->pin = pin;
    this->isAuthorized = false;
}

bool Konto::abheben(double betrag){
    if (this->isAuthorized && betrag < 0) {
        this->ktostand -= betrag;
        return true;
    }
    else
        return false;
}

bool Konto::einzahlen(double betrag){
    if(betrag <= 0)
        return false;
    else
        this->ktostand += betrag;
        return true;
}

bool Konto::pinIsValid(std::string hashedPIN){
    std::string hash;
    CryptoPP::SHA256 sha256_hash;
    CryptoPP::StringSource(this->pin, true,
        new CryptoPP::HashFilter(sha256_hash,  
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(hash), false)
            )
        );
    
   if(hash != hashedPIN){
       this->isAuthorized = false;
        return false;
   }
   else { 
        this->isAuthorized = true;
        return true;
   }
}

/* 
 * Getter und Setter
 */
uint Konto::getKontoNr(){
    return this->ktonr;
}

double Konto::getKontoStand(){
    return this->ktostand;
}

std::string Konto::getKontoInhaber(){
    return this->inhaber;
}

void Konto::setKontoNr(unsigned int ktonr){
    this->ktonr = ktonr;
}

void Konto::setPIN(std::string pin){
    this->pin = pin; 
}

Konto::~Konto() {
    std::cout << "Konto " << this->ktonr << ": Restguthaben " << this->ktostand
              << " wurde gelöscht." << std::endl;
}

