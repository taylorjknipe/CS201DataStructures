#include <iostream>
#include <cstdlib>
#include "CircularDynamicArray.cpp"

template <typename keytype, typename valuetype>
class Node
{
public:
    CircularDynamicArray<keytype> keys;
    CircularDynamicArray<valuetype> values;
    Node *children[4];
    int count;

    Node()
    {
        count = 0;
        for (int i = 0; i < 4; i++)
        {
            children[i] = nullptr;
        }
        keys = CircularDynamicArray<keytype>(3);
        values = CircularDynamicArray<valuetype>(3);
    }

    ~Node()
    {
        for (int i = 0; i < 4; i++)
        {
            if (children[i] != nullptr)
            {
                delete children[i];
            }
        }

        delete this->keys;
        delete this->values;
    }
};