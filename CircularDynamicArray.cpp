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
        this->frontIndex = 0;
        for (int i = this->size; i > 0; i--)
        {
            this->arr[i] = this->arr[i - 1];
        }
        this->arr[0] = item;
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
        this->arr[this->frontIndex] = T();
        for (int i = 0; i < this->size; i++)
        {
            this->arr[(this->frontIndex + i) % this->capacity] = this->arr[(this->frontIndex + i + 1) % this->capacity];
        }
        this->frontIndex = 0;
        arr[this->size - 1] = T();
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

    int partition(int l, int r)
    {
        int pivotIndex = l + rand() % (r - l + 1);

        swap(this->arr[pivotIndex], this->arr[r]);

        int x = this->arr[r], i = l;
        for (int j = l; j <= r - 1; j++)
        {
            if (this->arr[j] <= x)
            {
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(this->arr[i], this->arr[r]);
        return i;
    }

    T kthSmallest(int l, int r, int k)
    {
        if (k > 0 && k <= r - l + 1)
        {
            int index = partition(l, r);

            if (index - l == k - 1)
            {
                return this->arr[index];
            }

            if (index - l > k - 1)
            {
                return kthSmallest(l, index - 1, k);
            }

            return kthSmallest(index + 1, r, k - index + l - 1);
        }
        return -1;
    }

    T QSelect(int k)
    {
        return kthSmallest(0, this->size - 1, k);
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

    int linearSearch(T item)
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->arr[i] == item)
            {
                return i;
            }
        }
        return -1;
    }

    int binSearch(T item)
    {
        int left = 0;
        int right = this->size - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (this->arr[mid] == item)
            {
                return mid;
            }
            if (this->arr[mid] < item)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return -1;
    }
};