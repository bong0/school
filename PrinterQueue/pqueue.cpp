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

bool PQueue::containsJob(Knot* knot){
	if(this->isEmpty()) return false;
	Knot *bunny = this->head;
	do {
		if(bunny->job->id == knot->job->id) return true;
	}
	while(bunny = bunny->next);
	return false;
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
    if(this->containsJob(knot)) {Errors::isDuplicate(); return;}; //we don't want duplicates in our list
    if(!knot) Errors::outOfMem();
    if(isEmpty()){ // first item; we don't need to sort
		cout << "creating first item prio:" << knot->job->prio << endl;
        this->head = knot;
        this->tail = knot;
        knot->next = NULL;
        knot->prev = NULL;
    }
	else {
		Knot *right = this->tail;
		if(knot->job->prio < this->tail->job->prio){ // we have to search for the insertion pos
			right = this->head;
			while(prio > right->job->prio){ 
				//cout << "checking item " << *(right->job);
				right = right->next;
			}
			cout << "ended loop; right prio: " << right->job->prio << endl;
			/* begin insertion */
			if(knot->job->prio <= this->head->job->prio) { // we connect before head
				cout << "prepending prio:"<< knot->job->prio <<" before head" << endl;
				knot->next = this->head;
				this->head = knot;
				knot->prev = NULL;
				knot->next->prev = knot;
			}
			else if(right->job->prio >= knot->job->prio){ // we have to connect somewhere in the middle // FIXME (test if else is sufficient)
				cout << "connecting prio:"<< knot->job->prio <<" in middle of lid:" << knot->job->id  << " and r:"  << endl;
				knot->next = right; // connect knot forward
				knot->prev = right->prev; // connect knot left
				right->prev = knot; // connect right backward
				knot->prev->next = knot; // connect left forward
			}
		}
		else if(knot->job->prio >= this->tail->job->prio || right == this->tail){// we append to tail
			cout << "appending prio:"<< knot->job->prio <<" to tail" << endl;
			this->tail->next = knot; // was NULL previously
			knot->prev = this->tail; // connect back
			this->tail = knot; // set new tail;
			this->tail->next = NULL; // set nextreference to NULL
		}
	}
	cout << "added knot: " << *(knot->job);
	
	this->itemCount+=1;
	//this->show();
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
bool PQueue::printNextJob(){
	if(this->isEmpty()) return false;
	cout << "printing " << this->head->job << endl;
	this->pop();
	return true;
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
void Errors::isDuplicate(){
	cout << "[-] This one was a duplicate => discarding...";
}
void Errors::couldNotFindItem(){
	cout << "[-] Could not find that item, skipping..."<< endl;
}