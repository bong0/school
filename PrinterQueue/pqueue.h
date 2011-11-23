/* 
 * File:   pqueue.h
 * Author: bongo
 *
 * Created on November 3, 2011, 10:24 AM
 */

#pragma once
#include <string>

using namespace std;

class Knot;
class PrintJob;
class PQueue {
public:
    PQueue();
    PQueue(const PQueue& orig);
    virtual ~PQueue();
    void show();
    bool printNextJob();
    bool isEmpty();
    void newJob(long, long, string);
    void delJob(long id);
	void clear();
    void pop();
    
private:
    long itemCount;
    Knot* head;
    Knot* tail;
};
class Knot {
    friend class PQueue;
    public:
        Knot();
        Knot(long jobId, long prio, string data);
        ~Knot();
    private:
        Knot* next;
        Knot* prev;
        PrintJob* job;
};
class PrintJob {
    friend class PQueue;
    friend class Knot;
    friend ostream& operator<<(ostream&, PrintJob&);
    private:
        long id;
        long prio;
        string data;
};
class Errors {
    public:
        static void listEmpty();
        static void outOfMem();
		static void couldNotFindItem();
	private:
		Errors();
};
