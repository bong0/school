/* 
 * File:   main.cpp
 * Author: bongo
 *
 * Created on October 12, 2011, 8:39 PM
 */

#include "School.h"
#include <limits>
#include <boost/lexical_cast.hpp>

using namespace std;

int main() {
    unsigned long int studentNo=1; // need to get the initial entry into loop
    string sName="";
    School school;
    
    cout << "Schulverwaltung" << endl
         << "fügen sie Schüler hinzu, mit 0 beenden" << endl;

    while(1){
        if(sName!=""){
            School::Student student(sName, studentNo);
            school.getList().append(student); // FIXME (COPY Konstuktur benutzen)
        }
        else {
            cout << endl << "===============" << endl
                 << "Bitte geben sie einen Namen an!" << endl;
        }
        studentNo = 0;
        sName = "";
        cout << "===============" << endl
             << "Schülernummer: ";
        
        cin >> studentNo;
        if(studentNo==0) break;
        cout << "Name: ";
        cin.ignore(1); //weird bug; cin obviously leaves \n in buffer
        getline(cin, sName, '\n');
    }
    /**/
    int arr[]={8,2,5,13,4,19,12,6,3,11,10,7,9};
    for(int i=0; i<(sizeof(arr)/sizeof(int)); i++){
        School::Student student(boost::lexical_cast<string>(arr[i]), arr[i]);
        school.getList().append(student);
    }
   /**/ 
    cout << "Eingabe beendet." << endl
         << "=== BEGIN LISTING ===" << endl;
    school.getList().listAllCompact();
    cout << "=== END LISTING ===" << endl;
    school.getList().QuickSort();
    cout << "=== BEGIN LISTING ===" << endl;
    school.getList().listAllCompact();
    cout << "=== END LISTING ===" << endl;    
    return 0;
}

