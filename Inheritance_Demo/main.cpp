#include <iostream>
#include "myClasses.h"
#include "template_test.h"
#include <list>
using namespace std;

int main()
{
	B *bObj = new B();
	bObj->showId();
	K *kObj = new K;
	kObj->showSecretOfB();
	E *eObj = new E();
	eObj->showSecretOfK();
	
	delete bObj;
	delete kObj;
	delete eObj;
	
	cout << "BEGIN STACK DEMO" << endl;
	list<std::string>* stack = new list<std::string>;
	cout << "Size: " << stack->size() << std::endl;
	stack->push_front("foo");
	cout << "pushed: foo";
	cout << "Size: " << stack->size() << endl;
	delete stack;
	cout << "END STACK DEMO" << endl;
	
	//NumContainer<double> ncdObj = NumContainer<double>(3.14);
	//cout << "pow is: " << ncdObj.getPow2() << endl;
	
	return 0;
}
