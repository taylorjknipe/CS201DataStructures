#include <iostream>

template <class T>
class CircularDynamicArray
{
private:
    T *arr;
    int size;
    int capacity;
    int frontIndex;
};