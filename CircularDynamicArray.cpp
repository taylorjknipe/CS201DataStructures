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

    ~CircularDynamicArray()
    {
        delete[] arr;
    }

    CircularDynamicArray(const CircularDynamicArray& other)
    {
        this->size = other.size;
        this->capacity = other.capacity;
        this->arr = new T[this->capacity];
        this->frontIndex = other.frontIndex;

        for (int i = 0; i < this->size; i++)
        {
            this->arr[i] = other.arr[i];
        }
    }

    CircularDynamicArray& operator=(const CircularDynamicArray& other)
    {
        if (this != &other)
        {
            delete[] this->arr;

            this->size = other.size;
            this->capacity = other.capacity;
            this->arr = new T[this->capacity];
            this->frontIndex = other.frontIndex;

            for (int i = 0; i < this->size; i++)
            {
                this->arr[i] = other.arr[i];
            }
        }

        return *this;
    }
};