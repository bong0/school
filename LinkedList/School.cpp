/* 
 * File:   School.cpp
 * Author: bongo
 * 
 * Created on October 12, 2011, 8:39 PM
 */

#include "School.h"
#include <boost/lexical_cast.hpp> //casting ints to strings (when debugging)
#include <exception> //bad_alloc
using namespace std;

bool School::debug;

School::School() {
    debug = false;
}
School::School(bool debug) {
    this->debug = debug;
}

School::School(const School& orig) {
    // TODO implement
}

bool School::isDebugging(){
    return debug;
}

School::ListMaster& School::getList() {
    return this->lm;
}

/* Student */
School::Student::Student() {
    this->name = "NoName";
    this->studentNo = 0;
}

School::Student::Student(string name, unsigned long studentNo) {
    this->name = name;
    this->studentNo = studentNo;
}

ostream& operator<<(ostream& co, School::Student& student) {
    return co << "[" << student.studentNo << "]"
            << "Name: " << student.name;
}

/* Knot */
School::Knot::Knot() {
    this->next = NULL;
    this->prev = NULL;
}

/* ListMaster */
School::ListMaster::ListMaster() {
    this->head = NULL;
    this->tail = new Knot; /* we need a new knot w/o student data,
                            else we cannot determine the n-1 item */
    (this->tail->student).name = "Tail";
}

/* Listing Methods */
void School::ListMaster::listAll() {
    cout << "[[forward]]" << endl;
    Knot* bunny = this->head;
    while (bunny != this->tail && bunny != NULL) {
        cout << (bunny->student) << endl;
        bunny = bunny->next;
    }
    cout << "[[backward]]" << endl; //just demonstrating that I implemented backwards associativity
    bunny = this->tail->prev;
    while (bunny != NULL) {
        cout << (bunny->student) << endl;
        bunny = bunny->prev;
    }
}

void School::ListMaster::listAllCompact() { //creating single-line output for debugging mainly 
    Knot* bunny = this->head;
    if(bunny != this->tail && bunny != NULL){
        cout << "| ";
    }
    else {
        cout << endl << "[-] void" << endl;
        return;
    }
    while (bunny != this->tail) {
        cout << (bunny->student).studentNo << " | ";
        bunny = bunny->next;
    }
}

/* Insertion and Replacement Methods */
void School::ListMaster::prepend(Student& student) {
    Knot* knot = new Knot;
    knot->student = student;
    
    knot->next = this->head;
    knot->next->prev = knot; // backwards assoc of right knot
    this->head = knot;
    knot->prev = NULL; // backwards assoc of this knot is NULL (left border)
}

void School::ListMaster::append(Student& student) {
    Knot* knot;
    try {
         knot = new Knot; /* generate new Knot to insert */
    }
    catch(bad_alloc& excp){
        cout << "[FAIL] Couldn't allocate memory for list item ! => discarding"
             << "Error message was: " << excp.what() << endl;
        return;
    }
    knot->student = student;

    Knot* leftKnot = this->tail->prev; // we'll place knot to right of this one (if it exists)

    if(leftKnot != NULL) {
        leftKnot->next = knot; 
        knot->prev = leftKnot;
    } else { /* we insert the first element in the chain!
            * therefore set element as new head */
        this->head = knot;
        knot->prev = NULL;
    }   //we are the first element, we can omit the pointers
    knot->next = this->tail; //reference tail to right
    this->tail->prev = knot; // was leftKnot before
}

void School::ListMaster::insertBetween(Knot* toLeft, Knot* toRight, Knot* item) {
    // first make sure the knots around our source pos don't confuse
    // concat the right knot to the left knot seen from item in the middle
    item->next->prev = item->prev;
    item->prev->next = item->next;
    if(toLeft != NULL){ // "normal" case regular insert not at the front of the list
        // then prepare the target position and insert  
        item->prev = toLeft;
        toLeft->next = item;
 
    }
    else { // redefine head, we replace it
        item->prev = NULL;
    }
    item->next = toRight;
    toRight->prev = item;
    if(toLeft == NULL){
        this->head = item;
    }
    if(debug) cout << endl << "inserted " << item->student.studentNo
                   << " between " << ((toLeft!=NULL)?(boost::lexical_cast<string>(toLeft->student.studentNo)):"NULL") 
                   << " and "
                   << ((toRight!=NULL)?(boost::lexical_cast<string>(toRight->student.studentNo)):"NULL")  << endl;
    if(debug) this->listAllCompact();
}

void School::ListMaster::replace(Knot* kn1, Knot* kn2) {
    if (kn1->student.studentNo == kn2->student.studentNo) return; // we don't replace equal elements
    if(debug) cout << endl << "replacing " << (kn1->student).studentNo << " and " << (kn2->student).studentNo << endl;
    
    // replace data
    Student stud = kn2->student;
    kn2->student = kn1->student;
    kn1->student = stud;
    
    if(debug) this->listAllCompact();
}

/* Sorting Methods */
void School::ListMaster::QuickSort() { // convenience method
    cout << "Running QuickSort on List...";
    QuickSort(this->head, this->tail, NULL); // definition der initialen Sortiermenge
    cout << " done" << endl;
}

void School::ListMaster::QuickSort(Knot* left, Knot* right, Knot* lastPivot) {
    if(!left || !right) return; //no NULL pointers please!
    if(debug) cout << endl << "args: left:" << left->student.name << " right:" << right->student.name;
    Knot *rp = right, *lp = left, *pivot;

    if (left == right) return; // there's nothing to sort 
    else if (left->next == right) { // two elements
        if ((left->student).studentNo > (right->student).studentNo) {
            if(debug) cout << endl << "list bis only 2 elements big, replacing optimized"
                            << endl << "replacing " << (lp->student).name << " and " << (rp->student).name << endl;
            replace(lp, rp);
        }
        return;
    }

    if (right == this->tail) { // prüfe ob Kopf nicht das erste Element ist
        pivot = right->prev; //das letzte Element der (Teil-)Menge
        rp = right->prev->prev; //analog das Vorletzte
    } else {
        pivot = right;
        rp = right->prev;
    }

    if(debug) cout << endl << "lp: " << (lp->student).studentNo
                   << " rp: " << ((rp!=NULL)?(boost::lexical_cast<string>(rp->student.studentNo)):"NULL")
                   << " pivo: " << pivot->student.studentNo;

    /* Begin Partition-Loop*/
    while (1) {
        while ((lp->student).studentNo < (pivot->student).studentNo) {
            lp = lp->next; //find item bigger than pivot
            if(debug) cout << endl << "lp is " << ((lp!=NULL)?(boost::lexical_cast<string>(lp->student.studentNo)):"NULL");
            if (lp == rp || lp ==NULL) break; /* we don't have our relative pos to
                               * beginning or end neither to rp, so
                               * we need to do this check as a replacement of an if l<r*/
        }
        if (lp == rp || lp ==NULL) break; // break one level up
        while ((rp->student).studentNo > (pivot->student).studentNo) {
            rp = rp->prev; //find item smaller than pivot
            if(debug) cout << endl << "rp is " << (rp->student).name;
            if (lp == rp) break;
        }
        if (lp == rp) break;
        replace(lp, rp);
        if(debug) cout << endl << "lp: " << (lp->student).name << " rp: " << (rp->student).name;
    }
    if(!(pivot->student.studentNo > lp->student.studentNo)){ // catch condition in which pivot ist the biggest
        //right = pivot->prev; //prevent passing wrong right border to recursing funcs | pivot will be xchanged
        if (lp->prev != NULL) {
            insertBetween(lp->prev, rp, pivot); //lp->prev because lp did just ran into rp
        }
        else if(rp == left || lp ==NULL){ // catch condition if pivot is the smallest
            if(debug) cout << endl << "inserted " << pivot->student.studentNo << " at head pos";
            insertBetween(NULL, rp, pivot);
        } 
        else {
            insertBetween(lp, rp, pivot);
        }
    }
    
    if(debug){
        cout << endl << "lp: " << (lp->student).name << " rp: " << (rp->student).name << " pivot: "<< pivot->student.name << endl;
        this->listAllCompact();
        cout << endl << "recursing after paritioning" << endl;
    }
    if(debug) cout << endl << "sorting left";
    if(pivot->prev != this->head && lastPivot != right){ //if we wouldn't check this, left would be right of the 2nd arg, confusion...
        QuickSort(left, pivot->prev, pivot); // für linke Hälfte (überspringe letzten pivot)
    }
    if(debug) cout << endl << "finished processing left part" << endl
                   << "lp: " << (lp->student).studentNo << " rp: " << (rp->student).studentNo << " piv: " << (pivot->student).studentNo
                   << " left: " << (left->student).studentNo << " right: " << (right->student).studentNo << endl;
    
    if (right == this->tail) {
        if(pivot->next->student.studentNo != 0 && pivot != right){
            //QuickSort(rp, right->prev); // für rechte Hälfte
             if(debug) cout << endl << "sorting right (right is tail, pv->next!=nil)";
             QuickSort(pivot->next, right->prev, pivot); // für rechte Hälfte
        }
        else return;
    }
    else {
            //QuickSort(rp, right);
        if(pivot->next->student.studentNo != 0 && pivot != right) { //make sure the ranges don't overlap
                if(debug) cout << endl << "sorting right (right is not tail, pv->next!=nil)" << endl;   
                QuickSort(pivot->next, right, pivot);
        }
        else return;
    }

    if(debug) cout << endl << "finished processing right part" << endl;
}

/* The Destructor */
School::ListMaster::~ListMaster() {
    if(debug) cout << endl;
    /* clean dyn alloc mem by hopping through
     * the list throwing away the knots */
    Knot* bunny = this->head;
    Knot* nextHop;
    do {
        if (bunny == NULL) break;
        nextHop = bunny->next;
        if(debug) cout << "Hop, destroying student entry "
                << bunny->student.studentNo << " | "
                << (bunny->student).name << endl;
        delete bunny;
    }while (bunny = nextHop);
}