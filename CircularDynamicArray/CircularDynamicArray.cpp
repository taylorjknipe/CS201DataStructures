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

    int partition(T *temp, int l, int r)
    {
        int pivotIndex = l + rand() % (r - l + 1);

        std::swap(temp[pivotIndex], temp[r]);

        T pivot = temp[r];
        int i = l - 1;

        for (int j = l; j < r; j++)
        {
            if (temp[j] <= pivot)
            {
                i++;
                std::swap(temp[i], temp[j]);
            }
        }

        std::swap(temp[i + 1], temp[r]);
        return i + 1;
    }

    T kthSmallest(T *temp, int l, int r, int k)
    {
        if (k > 0 && k <= r - l + 1)
        {
            int index = partition(temp, l, r);

            if (index - l == k - 1)
            {
                return temp[index];
            }

            if (index - l > k - 1)
            {
                return kthSmallest(temp, l, index - 1, k);
            }

            return kthSmallest(temp, index + 1, r, k - index + l - 1);
        }
        return -1;
    }

    T QSelect(int k)
    {
        T *temp = new T[this->size];
        for (int i = 0; i < this->size; i++)
        {
            temp[i] = this->arr[(this->frontIndex + i) % this->capac];
        }
        T result = kthSmallest(temp, 0, this->size - 1, k);
        delete[] temp;
        return result;
    }

    void quickSort(T *temp, int left, int right)
    {
        if (left < right)
        {
            int pivot = partition(temp, left, right);
            quickSort(temp, left, pivot - 1);
            quickSort(temp, pivot + 1, right);
        }
    }

    void Sort()
    {
        T *temp = new T[this->size];
        for (int i = 0; i < this->size; i++)
        {
            temp[i] = this->arr[(this->frontIndex + i) % this->capac];
        }
        quickSort(temp, 0, this->size - 1);
        for (int i = 0; i < this->size; i++)
        {
            this->arr[(this->frontIndex + i) % this->capac] = temp[i];
        }
        delete[] temp;
    }

    int linearSearch(T item)
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->arr[(this->frontIndex + i) % this->capac] == item)
            {
                return i;
            }
        }
        return -1;
    }

    int binSearch(T item)
    {
        return binarySearcher(this->arr, this->frontIndex, this->frontIndex + this->size - 1, item);
    }
    
    int binarySearcher(T *arr, int l, int r, T key) {
        if (r >= l) {
            int mid = l + (r - l) / 2;
            if (arr[mid] == key) {
                return mid;
            } else if (arr[mid] > key) {
                return binarySearcher(arr, l, mid - 1, key);
            } else {
                return binarySearcher(arr, mid + 1, r, key);
            }
        }
        return -1;
    }
};