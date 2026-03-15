#pragma once 

class Array {
     int* ptr;
    int size, capacity;
    public:
    int& operator[](int index);
     void insert(int elem, int index);
    void remove(int index);
    explicit Array(int startCapacity =DEFAULT_CAPACITY);

    ~Array();
    Array(const Array& arr);
    
 
}