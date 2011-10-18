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
    School(const School& orig);
    virtual ~School();
    
     /* wir verzichten auf Datenkapselung da die ListMaster-Instanz
      * von School priv ist
      */
   
    class Student { // zu verwaltende Datenstruktur
        friend ostream& operator<<(ostream&, Student& student);
        public:
            Student();
            Student(string, unsigned long int);
            unsigned long studentNo;
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
          void insertBetween(Knot* toLeft, Knot* toRight, Knot* item);
          Student get(unsigned long number);
          void listAll(); 
          void listAllCompact();
          ~ListMaster();
        private:
          Knot *head;
          Knot *tail;
          void QuickSort(Knot*, Knot*); // we don't want to make the backend public
          void replace(Knot*, Knot*);
    };
    ListMaster& getList();
    
private:
    ListMaster lm;
};

