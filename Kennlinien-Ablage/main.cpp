/* 
 * File:   main.cpp
 * Author: bongo
 *
 * Created on September 22, 2011, 10:37 AM
 */

#include <cstdlib>
#include <iostream>

#include "KennlinienAblage.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int anzahl=0;
    cout << "Bitte geben sie die Anzahl der Kennlinien ein: ";
    cin >> anzahl;
    
    KennlinienAblage ka(anzahl);
    ka.setData();
    ka.show();
    return 0;
}

