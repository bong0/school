using namespace std;
#include "template_test.h"

template <class T>
NumContainer<T>::NumContainer(T num){
  this->num = num;
}

template <class T>
T NumContainer<T>::getPow2(){
  return (this->num * this->num);
}
