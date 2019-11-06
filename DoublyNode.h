#include <iostream>

using namespace std;

template <class T> class DoublyNode
{
    public:
        DoublyNode();
        DoublyNode(T d);
        ~DoublyNode();

        T data;
        DoublyNode<T> *next;
        DoublyNode<T> *prev;

};


template <class T> //declares template class
DoublyNode<T>::DoublyNode()
{
    data = nullptr;
    next = nullptr; //nullptr
    prev = nullptr;
}

template <class T> //declares template class
DoublyNode<T>::DoublyNode(T d)
{
    data = d;
    next = nullptr; //nullptr
    prev = nullptr;
}

template <class T> //declares template class
DoublyNode<T>::~DoublyNode()
{
    next = nullptr;
    prev = nullptr;
}
