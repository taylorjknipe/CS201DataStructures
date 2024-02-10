#include <iostream>

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
            this->arr[i] = other.arr[i];
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
        return binarySearcher(this->arr, this->frontIndex, this->frontIndex + this->size - 1, item);
    }

    int binarySearcher(T *arr, int l, int r, T key) {
        return 1;
    }
};