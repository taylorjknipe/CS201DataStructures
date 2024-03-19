#include <iostream>
#include <algorithm>
#include "Node.cpp"

template <typename keytype, typename valuetype>
class two4Tree
{
private:
    Node<keytype, valuetype> *root;

public:
    two4Tree()
    {
        root = nullptr;
    }

    two4Tree(keytype k[], valuetype V[], int s)
    {
        root = nullptr;
        for (int i = 0; i < s; i++)
        {
            insert(k[i], V[i]);
        }
    }

    ~two4Tree()
    {
        // TODO
    }

    valuetype *search(keytype k)
    {
        // TODO
    }

    void insert(keytype k, valuetype v)
    {
        if (root == nullptr)
        {
            root = new Node<keytype, valuetype>();
            root->keys.addEnd(k);
            root->values.addEnd(v);
            root->count = 1;
            return;
        }
        else if (root->count < 3)
        {
            root->keys.addEnd(k);
            root->values.addEnd(v);
            root->count++;
            return;
        }
    }

    void print()
    {
        if (root)
        {
            for (int i = 0; i < root->keys.length(); i++)
            {
                if (root->values[i])
                    std::cout << root->values[i] << std::endl;
            }
        }
    }
};

int main()
{
    two4Tree<char, int> T;
    T.insert('a', 1);
    T.insert('b', 2);
    T.insert('c', 3);
    T.print();
    return 0;
}