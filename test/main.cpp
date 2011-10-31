#include <iostream>
#include "T.h"
#include "container.h"

using namespace std;

void func(T obj);
int main(){
 T tobj;
 tobj.print();
 // some assignment:
 int testbuf[] = {1,6,2,65,7,3};
 T newtobj(testbuf, sizeof(testbuf)/sizeof(int));
 func(newtobj);
 cout << "betrag: " << newtobj.betrag() << endl;
 cout << "5+newtobj: " << 5+newtobj << endl;
 container c;
 cout << "cast from obj to int: (int)newtobj => " << (int)newtobj << endl;
 cin >> newtobj;
 newtobj.print();
}
void func(T obj){
    cout << "copied object via copyconstr:" << endl;
    obj.print();
}
