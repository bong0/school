/* 
 * File:   main.cpp
 * Author: bongo
 *
 * Created on October 12, 2011, 8:39 PM
 */

#include "School.h"
#include <stdlib.h>     //for rand() 
#include <time.h>       //needed for "random" seed
#include <boost/lexical_cast.hpp> //casting ints to strings (when debugging)

using namespace std;

int main() {
    unsigned long int studentNo=1; // need to get the initial entry into loop
    string sName="";
    School school(true);
    
    cout << "Schulverwaltung" << endl
         << "fügen sie Schüler hinzu, mit 0 beenden" << endl;

    if(school.isDebugging()){
        //TODO: implement random number generation 
        //int arr[]={8,2,5,13,4,19,12,6,3,11,10,7,9};
        unsigned long int max;
        unsigned long int currentRand;
        cout << "Debug-Modus ist eingeschaltet." << endl
             << "Bitte geben sie das Maximum der Menge der Zufallszahlen an: ";
        cin >> max;
        
        srand (time(NULL));
        for(; max > 0; max--){
            currentRand = (rand()%500)+1;
            School::Student student(boost::lexical_cast<string>(currentRand), currentRand);
            school.getList().append(student);
        }
    }
    else {
        while(1){
            if(sName!=""){
                School::Student student(sName, studentNo);
                school.getList().append(student); // FIXME (COPY Konstuktur benutzen)
            }
            else {
                cout << endl << string(20,'=') << endl
                     << "Bitte geben sie einen Namen an!" << endl;
            }
            studentNo = 0;
            sName = "";
            cout << string(20,'=') << endl
                 << "Schülernummer: "; //student number

            cin >> studentNo;
            if(studentNo==0) break;
            cout << "Name: ";
            cin.ignore(1); //weird bug; cin obviously leaves \n in buffer
            getline(cin, sName, '\n');
        } 
    }
    cout << "Eingabe beendet." << endl
    << "Listeninhalt vor Sortierung:" << endl;
    school.getList().listAllCompact();
    school.getList().QuickSort();
    cout << "Listeninhalt nach Sortierung:" << endl;
    school.getList().listAllCompact();
    
    return 0;
}

