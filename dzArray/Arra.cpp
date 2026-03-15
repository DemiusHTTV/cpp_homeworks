#include "headers/Array.h"
#include <iostream>

using namespace std;



Array::Array(int startCapacity){
    if(startCapacity <=0)
        capacity = DEFAULT_CAPACITY;
    else 
        capacity = startCapacity;
    ptr = new int[capacity];
    sizr = 0
 
}
   Array::~Array(){
        delete[] ptr ;
    }
Array::Aray(const Array &arr){
    
}