/* 
 * File:   School.cpp
 * Author: bongo
 * 
 * Created on October 12, 2011, 8:39 PM
 */

#include "School.h"
using namespace std;

School::School() {}

School::School(const School& orig) {
    // TODO implement
}

School::~School() {
    // TODO implement
}

School::ListMaster& School::getList(){
    return this->lm;
}


/* Student */
School::Student::Student(){
    this->name = "NoName";
    this->studentNo = 0;
}
School::Student::Student(string name, unsigned long studentNo){
    this->name = name;
    this->studentNo = studentNo;
}

ostream& operator<<(ostream& co, School::Student& student){
    return co << "[" << student.studentNo << "]"
              << "Name: " << student.name;
}
/* Knot */
School::Knot::Knot(){
    this->next = NULL;
}
/* ListMaster */
School::ListMaster::ListMaster(){
    this->head = this->tail = NULL;
}
void School::ListMaster::append(Student& student){
    Knot* knot = new Knot;
    knot->student = student;
    
    knot->next = this->head;
    this->head = knot;
}
void School::ListMaster::listAll(){
    Knot* bunny = this->head;
    while(bunny){
        bunny=bunny->next;
        cout << (bunny->student) << endl;
    }
}
School::ListMaster::~ListMaster(){
    /* clean dyn alloc mem by hopping through
     * the list throwing away the knots */
    Knot* bunny = this->head;
    Knot* nextHop;
    do {
        if(bunny==NULL) break;
        nextHop=bunny->next;
        cout << "Hop, destroying student entry "
             << bunny->student.studentNo << endl;
        delete bunny;
    }
    while(bunny=nextHop);
    cout << "cul8or, see ya on the haystack...-heap :)";
}