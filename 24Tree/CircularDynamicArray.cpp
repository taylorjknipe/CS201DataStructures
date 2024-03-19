#include <iostream>
#include <cstdlib>

template <class T>
class CircularDynamicArray
{
private:
    T *arr;
    int size;
    int capac;
    int frontIndex;
    void resize(int newCapacity)
    {
        T *temp = new T[newCapacity];
        for (int i = 0; i < this->size; i++)
        {
            temp[i] = this->arr[(this->frontIndex + i) % this->capac];
        }
        delete[] this->arr;
        this->arr = temp;
        this->capac = newCapacity;
        this->frontIndex = 0;
    }

public:
    CircularDynamicArray()
    {
        this->size = 0;
        this->capac = 2;
        this->arr = new T[this->capac];
        this->frontIndex = -1;
    }

    CircularDynamicArray(int s)
    {
        this->size = s;
        this->capac = s;
        this->arr = new T[this->capac];
        this->frontIndex = -1;
        for (int i = 0; i < s; i++)
        {
            this->arr[i] = T();
        }
    }

    ~CircularDynamicArray()
    {
        delete[] arr;
    }

    CircularDynamicArray(const CircularDynamicArray &other)
    {
        this->size = other.size;
        this->capac = other.capac;
        this->arr = new T[this->capac];
        this->frontIndex = other.frontIndex;

        for (int i = 0; i < this->size; i++)
        {
            this->arr[(i + frontIndex) % capac] = other.arr[(i + frontIndex) % capac];
        }
    }

    CircularDynamicArray &operator=(const CircularDynamicArray &other)
    {
        if (this != &other)
        {
            delete[] this->arr;

            this->size = other.size;
            this->capac = other.capac;
            this->arr = new T[this->capac];
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
        return this->arr[(this->frontIndex + i) % capac];
    }

    void addEnd(T item)
    {
        if (this->size == this->capac)
        {
            this->resize(this->capac * 2);
        }
        if (this->size == 0)
        {
            this->frontIndex = 0;
        }
        this->arr[(this->frontIndex + this->size) % this->capac] = item;
        this->size++;
    }

    void addFront(T item)
    {
        if (this->size == this->capac)
        {
            this->resize(this->capac * 2);
        }
        if (this->size == 0)
        {
            this->frontIndex = 0;
        }
        this->frontIndex = (this->frontIndex - 1 + this->capac) % this->capac;
        this->arr[frontIndex] = item;
        this->size++;
    }

    void delEnd()
    {
        if (this->size == 0)
        {
            std::cout << "Array is empty" << std::endl;
            return;
        }
        this->size--;
        if (this->size <= this->capac / 4)
        {
            this->resize(this->capac / 2);
        }
    }

    void delFront()
    {
        if (this->size == 0)
        {
            std::cout << "Array is empty" << std::endl;
            return;
        }
        this->frontIndex = (this->frontIndex + 1) % this->capac;
        this->size--;
        if (this->size <= this->capac / 4)
        {
            this->resize(this->capac / 2);
        }
    }

    int length()
    {
        return this->size;
    }

    int capacity()
    {
        return this->capac;
    }

    void clear()
    {
        delete[] this->arr;
        this->size = 0;
        this->capac = 2;
        this->arr = new T[this->capac];
        this->frontIndex = -1;
    }
};