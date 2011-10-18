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
    this->prev = NULL;
}
/* ListMaster */
School::ListMaster::ListMaster(){
    this->head = NULL;
    this->tail = new Knot; /* we need a new knot w/o student data,
                            else we cannot determine the n-1 item */
    (this->tail->student).name = "Tail";
}

/* Listing Methods */
void School::ListMaster::listAll(){
    cout << "[[forward]]" << endl;
    Knot* bunny = this->head;
    while(bunny != this->tail && bunny != NULL){
        cout << (bunny->student) << endl;
        bunny=bunny->next;
    }
    cout << "[[backward]]" << endl;
    bunny = this->tail->prev;
    while(bunny != NULL){
        cout << (bunny->student) << endl;
        bunny=bunny->prev;
    }
}
void School::ListMaster::listAllCompact(){
    cout << endl;
    Knot* bunny = this->head;
    while(bunny != this->tail && bunny != NULL){
        cout << (bunny->student).studentNo << " | ";
        bunny=bunny->next;
    }
}
/* Insertion and Replacement Methods */
void School::ListMaster::prepend(Student& student){
    Knot* knot = new Knot;
    knot->student = student;
    
    knot->next = this->head;
    knot->next->prev = knot; // backwards assoc of right knot
    this->head = knot;
    knot->prev = NULL; // backwards assoc of this knot is NULL (left border)
}
void School::ListMaster::append(Student& student){
    Knot* knot = new Knot;      /* generate new Knot to insert */
    knot->student = student;
    
    Knot* leftKnot = this->head;
    while(leftKnot && leftKnot->next && (leftKnot->next != this->tail)) { // suche das vorletzte Element
        leftKnot = leftKnot->next;
    }
    
    if(leftKnot != NULL) { 
        leftKnot->next = knot; // was tail, now is new knot; (left)NEW(tail)
        knot->prev = leftKnot;
    }
    else { /* we insert the first element in the chain!
            * therefore set element as new head */
        this->head = knot;
        knot->prev = NULL;
    }
    knot->next = this->tail;
    this->tail->prev = knot;
    this->tail->next = NULL;
}
void School::ListMaster::insertBetween(Knot* toLeft, Knot* toRight, Knot* item){
    // first make sure the knots around our source pos don't confuse
     // concat the right knot to the left knot seen from item in the middle
     item->next->prev = item->prev; 
     item->prev->next = item->next; 
    // then prepare the target position and insert  
    item->prev = toLeft;
    toLeft->next = item;
    item->next = toRight;
    toRight->prev = item;
}
void School::ListMaster::replace(Knot* kn1, Knot* kn2){
    if(kn1 == kn2) return; // we dont't replace equal elements
    /**/ cout << endl<< "replacing "<<(kn1->student).studentNo<<" and "<<(kn2->student).studentNo; /**/
    // replace data
    Student stud = kn2->student;
    kn2->student = kn1->student;
    kn1->student = stud;
    /**/ this->listAllCompact();
}

/* Sorting Methods */
void School::ListMaster::QuickSort(){ // convenience method
    cout << "Running QuickSort on List...";
    QuickSort(this->head, this->tail); // definition der initialen Sortiermenge
    cout << " done" << endl;
}
void School::ListMaster::QuickSort(Knot* left, Knot* right){
    /**/ cout << "args: left:"<<left->student.name<<" right:"<<right->student.name<<endl;
    Knot *rp=right, *lp=left, *pivot;

    if(left == right) return; // there's nothing to sort 
    else if(left->next == right){ // two elements 
        /**/ cout << endl << "list is only 2 elements big, replacing optimized";
        /**/ cout << endl<< "replacing "<<(left->student).name<<" and "<<(right->prev->student).name;
             
        if((left->student).studentNo > (right->student).studentNo){
            replace(lp, rp);
        }
        return;
    }
    
    //if(right->prev == this->head) return;  // da nur <= 1 Element existiert ist die Menge sortiert.
    if(right == this->tail) { // prüfe ob Kopf nicht das erste Element ist
        pivot = right->prev; //das letzte Element der (Teil-)Menge
        rp = right->prev->prev; //analog das Vorletzte
    }
    else {
        pivot = right;
        rp = right->prev;
    }

    /**/
     cout << endl << "DEBUG: name left: " << (lp->student).name
          << " right: " << (rp->student).name
          << " pivo: " << pivot->student.name;
    /**/
    /* Begin Partition-Loop*/
    while(1){
        while((lp->student).studentNo < (pivot->student).studentNo) {
            lp = lp->next; //find item bigger than pivot
            if(lp==rp) break; /* we don't have our relative pos to
                               * beginning or end neither to rp, so
                               * we need to do this check as a replacement of an if l<r*/
            /**/
            cout << endl << "left is " << (lp->student).name;
            /**/
        }
        if(lp==rp) break; // break one level up
        while((rp->student).studentNo > (pivot->student).studentNo) {
            //if((rp->student).studentNo < 1) break; // out of range
            rp = rp->prev; //find item smaller than pivot
            /**/
            cout << endl << "right is " << (rp->student).name;
            /**/
        }
        replace(lp, rp);
        /**/ cout << endl<< "lp: "<< (lp->student).name << " rp: " << (rp->student).name;
    }
    if(lp->prev != NULL){
        insertBetween(lp->prev, rp, pivot); //lp->prev because lp did just ran into rp
    }
    else {
        insertBetween(lp, rp, pivot);
    }
    /**/ cout << endl<< "lp: "<< (lp->student).name << " rp: " << (rp->student).name;
    /**/ this->listAllCompact();
     cout << endl << "calling recursion after partitioning" << endl;
    /**/
    QuickSort(left, pivot->prev); // für linke Hälfte (überspringe letzten pivot)
    /**/ cout << endl<< "finished processing left part"<< endl
              << "lp: "<<(lp->student).studentNo<<" rp: "<<(rp->student).studentNo<<" piv: "<<(pivot->student).studentNo
              << " left: "<<(left->student).studentNo<<" right: "<<(right->student).studentNo << endl;
    if(right == this->tail){
        if(rp->student.studentNo <= right->prev->student.studentNo){
            QuickSort(rp, right->prev); // für rechte Hälfte
        }
    }
    else {
        if(rp->student.studentNo <= right->student.studentNo){
            QuickSort(rp, right); // für rechte Hälfte
        }
    }
    
         /**/ cout << endl<< "finished processing right part" << endl;
}

/* The Destructor */
School::ListMaster::~ListMaster(){
    /* clean dyn alloc mem by hopping through
     * the list throwing away the knots */
    Knot* bunny = this->head;
    Knot* nextHop;
    do { 
        if(bunny==NULL) break;
        nextHop=bunny->next;
        cout << "Hop, destroying student entry "
             << bunny->student.studentNo << " | "
             << (bunny->student).name << endl;
        delete bunny;
    }
    while(bunny=nextHop);
}