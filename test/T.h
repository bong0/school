#ifndef CLASS_T
#define CLASS_T
class T {
    friend class container;
 public:
        T();
        T(int[], int length);
        T(T&); // copy-konstruktor
        ~T();
        void print();
        int length();
        int betrag();
        int get(int index);
        T& operator=(T&);
 private:
        int *arr;
        int arrLength; // it's NOT possible to do a sizeof(arr) with correct results
        void outofmem();
};
int operator+(int, T&);

#endif
