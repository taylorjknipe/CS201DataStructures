#include <iostream>

template <class T>
class CircularDynamicArray
{
private:
    T *arr;
    int size;
    int capacity;
    int frontIndex;
    void resize(int newCapacity)
    {
        T *temp = new T[newCapacity];
        for (int i = 0; i < this->size; i++)
        {
            temp[i] = this->arr[(this->frontIndex + i) % this->capacity];
        }
        delete[] this->arr;
        this->arr = temp;
        this->capacity = newCapacity;
        this->frontIndex = 0;
    }

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

    CircularDynamicArray(const CircularDynamicArray &other)
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

    CircularDynamicArray &operator=(const CircularDynamicArray &other)
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

    T &operator[](int i)
    {
        if (i < 0 || i >= this->size)
        {
            std::cout << "Index out of bounds" << std::endl;
        }
        return this->arr[i];
    }

    void addEnd(T item)
    {
        if (this->size == this->capacity)
        {
            this->resize(this->capacity * 2);
        }
        this->arr[(this->frontIndex + this->size) % this->capacity] = item;
        this->size++;
    }

    void addFront(T item)
    {
        if (this->size == this->capacity)
        {
            this->resize(this->capacity * 2);
        }
        this->frontIndex = (this->frontIndex - 1 + this->capacity) % this->capacity;
        this->arr[this->frontIndex] = item;
        this->size++;
    }

    void delEnd()
    {
        if (this->size == 0)
        {
            std::cout << "Array is empty" << std::endl;
            return;
        }
        delete &this->arr[(this->frontIndex + this->size - 1) % this->capacity];
        this->size--;
        if (this->size <= this->capacity / 4)
        {
            this->resize(this->capacity / 2);
        }
    }

    void delFront() {
        if (this->size == 0)
        {
            std::cout << "Array is empty" << std::endl;
            return;
        }
        delete &this->arr[this->frontIndex];
        this->frontIndex = (this->frontIndex + 1) % this->capacity;
        this->size--;
        if (this->size <= this->capacity / 4)
        {
            this->resize(this->capacity / 2);
        }
    }
};  