/* 
 * File:   main.cpp
 * Author: bongo
 *
 * Created on September 22, 2011, 10:37 AM
 */

#include <cstdlib>
#include <iostream>
#include <limits>

#include "KennlinienAblage.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int anzahl=0;
    float tmp, get_val=-1;
    cout << "Bitte geben sie die Anzahl der Kennlinien ein: ";
    cin >> anzahl;
    
    KennlinienAblage ka(anzahl);
    ka.setData();
    ka.show();
    
    cout << "Den zugehörigen U-Wert finden: ";
    cin >> tmp;
    
    if((get_val = ka.getU(tmp))>(numeric_limits<float>::min())){
        cout << "Ausgabe: " << get_val << endl;
    }
    else {
        cout << "Error!" << endl;
    }
    
    cout << "Wir kopieren ein Objekt mithilfe des copykonstruktors: "
         << "KennlinienAblage ka1(ka);" << endl;
    KennlinienAblage ka1(ka);
    ka1.show();
    cout << "Ein Test des Zuweisungsops: ka2 = ka1;" << endl;
    KennlinienAblage ka2(ka);
    ka2 = ka1;
    ka2.show();

    
            
    return 0;
}

