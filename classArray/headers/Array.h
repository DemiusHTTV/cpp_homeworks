#pragma once 
using namespace std;
class ArrayException {};

const int DEFAULT_CAPACITY=10;
class Array {
     int* ptr;
    int size, capacity;
    void increaseCapacity(int newCapacity);
  
    public:
    explicit Array(int startCapacity = DEFAULT_CAPACITY);
    Array(const Array& arr);
    ~Array();
    Array& operator =(const Array& arr);
    int& operator[](int index);
    void insert(int elem, int index);
    void insert(int elem);  
    void remove(int index);
    int getSize() const;
    friend ostream& operator <<(ostream& out, const Array& arr);

    
 
};