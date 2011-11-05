/* 
 * File:   PQueue.cpp
 * Author: bongo
 * 
 * Created on November 3, 2011, 10:24 AM
 */

#include "PQueue.h"
#include <cstdlib>
#include <iostream>

using namespace std;

/* PrinterQueue List Manager */
PQueue::PQueue(): head(NULL), tail(NULL), itemCount(0) {}

PQueue::PQueue(const PQueue& orig) {}

PQueue::~PQueue() {
    Knot* bunny = this->head;
    Knot* nextHop = bunny;
    while((bunny = nextHop)->next) {
        nextHop = bunny->next;
        cout << "popping printjob " << *(bunny->job);
        delete bunny;
    }
}
void PQueue::show(){
    Knot* bunny;
    if((bunny = this->head) == NULL){
        Errors::listEmpty();
        return;
    }
    cout << "LISTING:" << endl;
    do {
        cout << *(bunny->job);
        bunny = bunny->next;
    }
    while(bunny->next != NULL);
}
bool PQueue::printNextJob(){
    cout << "Printing " << this->head->job;
    this->pop();
    return true; // useless
}
void PQueue::pop(){
    if(isEmpty()) return;
    this->head->next->prev = this->head; // just temp
    this->head = this->head->next; // move head one forward
    delete this->head->prev; // delete old head
    this->head->prev = NULL; // finish setting
}

void PQueue::newJob(long jobId, long prio, string data){
    Knot* knot = new Knot(jobId, prio, data);
    if(isEmpty()){
        if(!knot) Errors::outOfMem();
        this->head = knot;
        this->tail = knot;
        knot->next = NULL;
        knot->prev = NULL;
    }
    this->tail->next = new Knot(jobId, prio, data); // was NULL previously
    this->tail->next->prev = this->tail; // connect back
    this->tail = this->tail->next; // set new tail;
    this->tail->next = NULL; // set nextreference to NULL
}
void PQueue::delJob(long id){
    if(this->isEmpty()) return;
    Knot* bunny = this->head;
    do {
        if(bunny->job->id == id){
            if(bunny == this->head) this->pop();
            else if(bunny == this->tail){
                this->tail = this->tail->prev; // move tail backwards (left)
                delete this->tail->next;// delete old tail
                this->tail->next = NULL; // correct forward reference
            }
            else { // ok, we're somewhere in the middle of the queue
                bunny->prev->next = bunny->next; // connect forward
                bunny->next->prev = bunny->prev; // connect backward
                delete bunny; // cu
            }
        }
    }
    while(this->head != this->tail);
}
bool PQueue::isEmpty(){
    if(this->head == NULL && this->tail == NULL) return true;
    else return false;
}
/* Knot */
Knot::Knot(): next(NULL), prev(NULL), job(new PrintJob){
    if(!job) Errors::outOfMem();
}
Knot::Knot(long jobId, long prio, string data): next(NULL), prev(NULL), job(new PrintJob) {
    if(!job) Errors::outOfMem(); // yes, redundant, and gcc still doesn't support delegating constructors
    job->id = jobId;
    job->prio = prio;
    job->data = data;
}

Knot::~Knot(){
    delete this->job;
}

/* PrintJob */
ostream& operator<<(ostream& out, PrintJob& job){
    out << "ID: " << job.id << " Priority: " << job.prio << " Payload: " << job.data << endl;
}
    
void Errors::outOfMem(){
    cout << "[FATAL] We ran out of heap space !" << endl
         << "EXITING..." << endl;
    exit(1);
}
void Errors::listEmpty(){
    cout << "[-] The list is empty" << endl;
}