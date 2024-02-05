#include <iostream>

template <class T>
class CircularDynamicArray
{
private:
    T *arr;
    int size;
    int capacity;
    int frontIndex;

public:
    CircularDynamicArray()
    {
        this->size = 0;
        this->capacity = 2;
        this->arr = new T[this->capacity];
        this->frontIndex = -1;
    }
    CircularDynamicArray(int s)
    {
        this->size = s;
        this->capacity = s;
        this->arr = new T[this->capacity];
        this->frontIndex = -1;
    }
};