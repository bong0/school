/* 
 * File:   main.cpp
 * Author: bongo
 *
 * Created on August 16, 2011, 9:45 AM
 */

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/sha.h>
#include "./Konto.h"

#define CLR "\033[2J\033[1;1H"

using namespace std;

bool pinCheck(Konto *konto);
void welcome();
bool einzahlen(Konto *konto);
bool abheben(Konto *konto);
Konto* kto_anlegen(Konto *konto);
bool ktonr_aendern(Konto *konto);

/*
 * obj1=obj2 // Attributkopie ! operator überladen howto
 */

int main() {
    Konto *konto = NULL;
    char sel = 0;


    while(sel != 'q') {   
        if(konto == NULL)
            welcome();
        else {
            cout << "Willkommen " << konto->getKontoInhaber() << "!" <<endl;
            cout << "Konto: " << konto->getKontoNr() << " Kontokorrent: " << konto->getKontoStand() << endl;
                
            cout << "Wählen sie eine der folgenden Optionen:" << endl
                 << "1) Geld Einzahlen" << endl
                 << "2) Geld Abheben" << endl;
        }
        cout << "3) Neues Konto anlegen" << endl;
        if(konto != NULL)
                cout << "4) Kontonummer ändern" << endl;
        cout << "q) Terminal schließen" << endl;

        cin >> sel;
        switch(sel){
            case '1':
                einzahlen(konto);
                break;
            case '2':
                abheben(konto);
                break;
            case '3':
                konto = kto_anlegen(konto);
                break;
            case '4':
                ktonr_aendern(konto);
                break;
            case 'q':
                exit(0);
        } // end switch

    } // end while 
    return 0;
} // end main

void welcome(){
    cout << "Willkommen beim Banking-Terminal der Reichsbanken-Hufeisenbanken" << endl
         << "(Ihre Daten sind nicht nur uns wichtig, daher verschlüsseln wir selbststverständlich nicht.)\n" << endl;
    return;
}
bool pinCheck(Konto *konto){
    string pin;
    cout << "PIN: ";
    cin >> pin;
            
    std::string hash;
    CryptoPP::SHA256 sha256_hash;
    CryptoPP::StringSource(pin, true,
        new CryptoPP::HashFilter(sha256_hash,  
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(hash), false)
            )
        );
  
    cout << "Ihre PIN wird sha256 gehashed als 0x" << hash << " übertragen" << endl;
    if(konto->pinIsValid(hash))
        return true;
    else
        return false;
}
    
bool einzahlen(Konto *konto){
    double betrag = 0.0;
    
    cout << "Betrag: ";
    cin >> betrag;
    if(konto->einzahlen(betrag)){
        cout << "Buchung erfolgreich." << endl << CLR;
        return true;
    }
    else {
        cout << "Buchung fehlgeschlagen." << endl << CLR;
        return false;
    }
}

bool abheben(Konto *konto){
    double betrag = 0.0;
    
    if(pinCheck(konto)){
        cout << "Betrag: ";
        cin >> betrag;
        konto->abheben(betrag);
        cout << "Buchung erfolgreich." << endl << CLR;
        return true;
    }
    else {
        cout << "Bitte überprüfen sie ihre Eingabe und versuchen sie es erneut." << endl;
        return false;
    }
}

Konto* kto_anlegen(Konto *konto){
    double betrag = 0.0;
    uint ktonr = 0;
    string inhaber;
    string pin;

    do {
        cout << "Kontonummer: ";
        cin >> ktonr;
    }
    while(!ktonr);
    
    if(!betrag)
        betrag = 0;
    cout << "Startkorrent: ";
    cin >> betrag;
    
    do{
        cout << "Inhaber: ";
        cin >> inhaber;
    }while (inhaber == "");
    
    do{
        cout << "PIN: ";
        cin >> pin;
    }while (pin == "");
    
    
    if(konto != NULL){
        cout << "Das aktivierte Konto wird gelöscht!" << endl
             << "Möchten sie fortfahren?[y/N] ";
        if(tolower(getchar()) == 'y')
            delete konto;
    } 
    else  
       konto = new Konto(ktonr, betrag, inhaber, pin);
    
    if(!konto){
        cout << "Erstellen des Kontos fehlgeschlagen!" << endl << CLR;
        return NULL;
    }
    else {
        cout << CLR;
        return konto;
    }
}

bool ktonr_aendern(Konto *konto){
    uint ktonr = 0;
    
    do {
        cout << "Kontonummer: ";
        cin >> ktonr;
    }
    while(!ktonr);
    konto->setKontoNr(ktonr);
    cout << "Neue Kontonummer " << ktonr << " gesetzt" << endl;
    
    return true;
}