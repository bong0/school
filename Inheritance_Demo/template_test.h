#ifndef TEMPLATE_TEST_H
#define TEMPLATE_TEST_H

template <class T>
class NumContainer {
  private:
    T num;
  public:
    NumContainer(T num);
    T getPow2();
};
#endif // TEMPLATE_TEST_H
