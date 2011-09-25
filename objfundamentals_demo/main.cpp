/* 
 * File:   main.cpp
 * Author: bongo
 *
 * Created on September 7, 2011, 6:09 PM
 */

#include <cstdlib>
#include <iostream>
#include <exception>
#include "Fan.h"

using namespace std;

/* Eine Demonstration von ein Paar Grundlagen der OOO
 * zum Verdeutlichen der Prinzipien...
 */
int main(int argc, char** argv) {
    int x=4,
        &u=x; // Referenz auf x
    cout << "x: " << x << endl
         << "u: " << u << endl;
    u=17;
    cout << "nach u=17..." << endl
         << "x: " << x     << endl;
    
    Fan* fan1;
    try {
        fan1 = new Fan(); // wird durch die Initialisierungsliste befüllt
    }
    catch(bad_alloc){ // exception-handling
        cout << "[-] Ein Fehler beim Alloziieren des Speicherplatzes für \"fan1\""
                "trat auf. "
             << "verlasse das Programm..." << endl;
        exit(42);
    }
    fan1->print();
    
    /* mal ausproben:: * auf referenzen
     string.assign("a").assign("b")
     * was passiert bei const int a; // wert?
     * konstruktor der bei anonym. aufruf arbeitet?
     */
    delete fan1;
    return 0;
}

class Divide {
private:
    double zaehler, nenner;
public:
    Divide(double zaehler, double nenner):zaehler(zaehler),
                   nenner( (nenner==0.0)?:(cout<<"you divided by zero"),nenner ){
                                              /*warum ist als Ziel nicht this->var gültig? */
        try {
             std::cout << zaehler << "/" << nenner << "=" << nenner;
        }
        catch(exception& excp){
            cout << excp.what() << endl;
        }        
    }

};

