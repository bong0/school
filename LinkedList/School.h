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
    class Knot { // ein Knoten für einfach-direktionale Assoziation
        public:   
            Knot();
            Knot *next;
            Student student;
    };
    class ListMaster { // ListMaster speichert metadaten der Liste (Anfang,Ende)
        public:
          ListMaster();          
          void QuickSort();
          void append(Student&);
          void autoInsert(Student&);
          Student get(unsigned long number);
          void listAll();
          ~ListMaster(); 
        private:
          Knot *head;
          Knot *tail;
    };
    ListMaster& getList();
    
private:
    ListMaster lm;
};

