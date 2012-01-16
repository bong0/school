#ifndef CLASSES_H
#define CLASSES_H
#include <string>
using namespace std;

//######### Demo of regular inheritance
class B {
private:
	std::string secret;
protected:
	std::string getSecret();
public:
	B();
	void showId();
};

class K: protected B {
public:
	void showSecretOfB();
};

class E: protected K {
public:
	void showSecretOfK();
};

//########## Demo of multiple inheritance
class Shape {
protected:
	double area;
	std::string name;
public:
	double getArea();
	std::string getName();

};

#endif // CLASSES_H
