#include <iostream>
#include "T.h"

using namespace std;

void func(T obj);
int main(){
 T tobj;
 tobj.print();
 // some assignment:
 int testbuf[] = {1,6,2,65,7,3};
 T newtobj(testbuf, sizeof(testbuf)/sizeof(int));
 func(newtobj);
 
}
void func(T obj){
    cout << "copied object via copyconstr:" << endl;
    obj.print();
}
