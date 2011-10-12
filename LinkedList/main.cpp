/* 
 * File:   main.cpp
 * Author: bongo
 *
 * Created on October 12, 2011, 8:39 PM
 */

#include "School.h"

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
            cout << "===============" << endl
                 << "Bitte geben sie einen Namen an!" << endl;
        }
        studentNo = 0;
        sName = "";
        cout << "===============" << endl
             << "Schülernummer: ";
        
        cin >> studentNo;
        if(studentNo==0) break;
        cout << "Name: ";
        cin >> sName;
    }
    
    return 0;
}

