/* 
 * File:   container.cpp
 * Author: bongo
 * 
 * Created on October 31, 2011, 4:58 PM
 */

#include "container.h"
#include "T.h"
#include <iostream>

using namespace std;

container::container():value(new int){
    T t;

    if(!value){
        t.outofmem(); // whoa I can use another class' methods
    }
    else {
        cout << "I can haxxor into private attrs of an object of another class"<< endl
             << "=> t.arr's default length is:" << t.arrLength << endl;
    }
}

