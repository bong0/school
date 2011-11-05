/* 
 * File:   main.cpp
 * Author: bongo
 *
 * Created on November 3, 2011, 10:15 AM
 */

#include <cstdlib>
#include <iostream>
#include "PQueue.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    PQueue pq;
    cout << "Printer Queue is Empty: " << pq.isEmpty() << endl;
    pq.newJob(42, 1, "TestJob");
    pq.show();
    
    return 0;
}

