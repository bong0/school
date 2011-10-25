/* 
 * File:   School.h
 * Author: bongo
 *
 * Created on October 12, 2011, 8:39 PM
 */

#pragma once
#include <string>
#include <iostream>
using namespace std;

class School {
public:
    School();
    School(bool debug);
    School(const School& orig);
    bool isDebugging();
    
     /* wir verzichten auf Datenkapselung da die ListMaster-Instanz
      * von School priv ist
      */
   
    class Student { // zu verwaltende Datenstruktur
        friend ostream& operator<<(ostream&, Student& student);
        public:
            Student();
            Student(string, unsigned long int);
            unsigned long int studentNo;
            string name;
            
    };
    class Knot { // ein Knoten für bidirektionale Assoziation
        public:   
            Knot();
            Knot *next;
            Knot *prev; //previous
            Student student;
    };
    class ListMaster { // ListMaster speichert metadaten der Liste (Anfang,Ende)
        public:
          ListMaster();          
          void QuickSort(); 
          void append(Student&);
          void prepend(Student&);
          void autoInsert(Student&);
          Student get(unsigned long number);
          void listAll(); 
          void listAllCompact();
          ~ListMaster();
        private:
          Knot *head;
          Knot *tail;
          void QuickSort(Knot*, Knot*, Knot* lastPivot); // we don't want to make the backend public
          void replace(Knot*, Knot*);
          void insertBetween(Knot* toLeft, Knot* toRight, Knot* item);
    };
    ListMaster& getList();
    
private:
    ListMaster lm;
    static bool debug;
};