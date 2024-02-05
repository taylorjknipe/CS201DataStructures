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

    void delFront()
    {
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

    int length()
    {
        return this->size;
    }

    int getCapacity()
    {
        return this->capacity;
    }

    void clear()
    {
        delete[] this->arr;
        this->size = 0;
        this->capacity = 2;
        this->arr = new T[this->capacity];
        this->frontIndex = -1;
    }

    T QSelect(int k)
    {
        if (k < 0 || k >= this->size)
        {
            std::cout << "Invalid value of k" << std::endl;
            return T(); // Return default value of type T
        }
        T *tempArr = new T[this->size];
        for (int i = 0; i < this->size; i++)
        {
            tempArr[i] = this->arr[i];
        }
        int left = 0;
        int right = this->size - 1;
        while (left <= right)
        {
            int pivotIndex = left + (right - left) / 2;
            T pivotValue = tempArr[pivotIndex];
            int i = left;
            int j = right;
            while (i <= j)
            {
                while (tempArr[i] < pivotValue)
                {
                    i++;
                }
                while (tempArr[j] > pivotValue)
                {
                    j--;
                }
                if (i <= j)
                {
                    std::swap(tempArr[i], tempArr[j]);
                    i++;
                    j--;
                }
            }
            if (k <= j)
            {
                right = j;
            }
            else if (k >= i)
            {
                left = i;
            }
            else
            {
                delete[] tempArr;
                return tempArr[k];
            }
        }
        delete[] tempArr;
        return T(); // Return default value of type T
    }
    void merge(T *arr, int left, int mid, int right)
    {
        int leftSize = mid - left + 1;
        int rightSize = right - mid;

        T *leftArr = new T[leftSize];
        T *rightArr = new T[rightSize];

        for (int i = 0; i < leftSize; i++)
        {
            leftArr[i] = arr[left + i];
        }

        for (int i = 0; i < rightSize; i++)
        {
            rightArr[i] = arr[mid + 1 + i];
        }

        int i = 0;
        int j = 0;
        int k = left;

        while (i < leftSize && j < rightSize)
        {
            if (leftArr[i] <= rightArr[j])
            {
                arr[k] = leftArr[i];
                i++;
            }
            else
            {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        while (i < leftSize)
        {
            arr[k] = leftArr[i];
            i++;
            k++;
        }

        while (j < rightSize)
        {
            arr[k] = rightArr[j];
            j++;
            k++;
        }

        delete[] leftArr;
        delete[] rightArr;
    }

    void mergeSort(T *arr, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    void Sort()
    {
        mergeSort(this->arr, 0, this->size - 1);
    }
};