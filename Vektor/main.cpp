/* 
 * File:   main.cpp
 * Author: bongo
 *
 * Created on August 30, 2011, 8:24 AM
 */

#include <cstdlib>
#include <iostream>
#include "Vektor.h"

using namespace std;

int main() {
    Vektor v1,v2(3.1,2.2,4.4);
    Vektor *pv = new Vektor;
    
    cout<<"v1.show(): "<< v1.show() << endl
        <<"v2.show(): "<< v2.show() << endl;
    pv->setX(0.2);
    pv->setY(0.4);
    pv->setZ(0.6);
    cout<<"pv->Betrag(): " << pv->Betrag() << endl;
    cout<<"(pv->vadd(v2)).show(): " << (pv->vadd(v2)).show() << endl;
    cout<<"(oder mittels operator+: (*pv+v2).show(): " <<
           (*pv+v2).show() << endl;
    cout<<"wir berechnen den Betrag pvs mithilfe des überladenen operator+ und addieren 7"
        <<endl << *pv+7.0 <<endl;
    delete pv;
    return 0;
}

