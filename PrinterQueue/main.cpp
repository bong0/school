/* 
 * File:   main.cpp
 * Author: bongo
 *
 * Created on November 3, 2011, 10:15 AM
 */

#include <cstdlib>
#include <iostream>
#include <time.h> // for rand seed
#include "pqueue.h"
using namespace std;

int main(int argc, char** argv) {
    PQueue pq;
    cout << "Printer Queue is Empty: " << pq.isEmpty() << endl;
	srand(time(NULL));
    for(int i=0; i<10; i++){
		pq.newJob(i, rand()%50, "TestJob");
	}
    pq.show();
    pq.delJob(5);
	pq.delJob(9);
    cout << "Printer Queue is Empty: " << pq.isEmpty() << endl;
	pq.clear();
    cout << "Printer Queue is Empty: " << pq.isEmpty() << endl;
	
    return 0;
}

