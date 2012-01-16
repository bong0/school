#include <iostream>
#include "myClasses.h"
using namespace std;

B::B(){
	this->secret = "FOSS is great!";
}
std::string B::getSecret(){
	return this->secret;
}
void B::showId(){
	std::cout << "Hello, I'm mother class B!" << std::endl;
}

void K::showSecretOfB(){
	std::cout << "The secret of B is not accessible via the attribute!" << /*this->secret <<*/ std::endl;
	std::cout << "But it's accessible via a protected method I (K) inherited: " << this->getSecret() << std::endl;
}

void E::showSecretOfK(){
	std::cout << "showSecret from B is still accessible due to all-proctected inheritance: " << this->getSecret() << std::endl;
	std::cout << "of course, public methods of B are still available to methods of E & K: "; this->showId();
}


