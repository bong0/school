/*
* File: PQueue.cpp
* Author: bongo
*
* Created on November 3, 2011, 10:24 AM
*/

#include "pqueue.h"
#include <cstdlib>	//exit()
#include <iostream>

using namespace std;

/* PrinterQueue List Manager */
PQueue::PQueue(): head(NULL), tail(NULL), itemCount(0) {}

PQueue::~PQueue() {
	this->clear();
}
void PQueue::clear(){
	if(isEmpty()) return; // we don't mess with NULL pointers
	cout << "clearing list..." << endl;
	Knot* bunny = this->head;
    Knot* nextHop = bunny;
	do {
		nextHop = bunny->next;
        cout << "popping printjob " << *(bunny->job);
        delete bunny;
		this->itemCount-=1;
    }
    while(bunny = nextHop);
	this->head = this->tail = NULL;
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
    while(bunny != NULL);
	cout << "Item Count: " << this->itemCount << endl;
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
	this->itemCount-=1;
}

void PQueue::newJob(long jobId, long prio, string data){
    Knot* knot = new Knot(jobId, prio, data);
    if(!knot) Errors::outOfMem();
    if(isEmpty()){
        this->head = knot;
        this->tail = knot;
        knot->next = NULL;
        knot->prev = NULL;
    }
	else {
	    this->tail->next = new Knot(jobId, prio, data); // was NULL previously
		this->tail->next->prev = this->tail; // connect back
		this->tail = this->tail->next; // set new tail;
		this->tail->next = NULL; // set nextreference to NULL
	}
	this->itemCount+=1;
}
void PQueue::delJob(long id){
    if(this->isEmpty()) return;
    Knot* bunny = this->head;
	if(this->head == this->tail){
		this->head = this->tail = NULL;
		cout << "deleting job id: " << bunny->job->id << endl;
		delete bunny;
		this->itemCount-=1;
		return;
	}
	if(bunny->job->id == id){
		cout << "deleting job id: " << bunny->job->id << endl;
		this->pop();
	}
	else { 	// ok, we're somewhere in the middle of the queue
			// do linear search
		do {
			bunny = bunny->next;
		}
		while(bunny != NULL && bunny->job->id != id);
		if(bunny == NULL){
			Errors::couldNotFindItem();
			return;
		}
		if(bunny == this->tail && (bunny->job->id == id)){
			cout << "deleting job id: " << bunny->job->id << endl;
			this->tail = this->tail->prev; // move tail backwards (left)
			delete this->tail->next;// delete old tail
			this->tail->next = NULL; // correct forward reference
			this->itemCount-=1;
			return;
		}
		bunny->next->prev = bunny->prev; // connect backward
		bunny->prev->next = bunny->next; // connect forward
		cout << "deleting job id: " << bunny->job->id << endl;
		delete bunny; // cu
		this->itemCount-=1;
	}
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
void Errors::couldNotFindItem(){
	cout << "[-] Could not find that item, skipping..."<< endl;
}