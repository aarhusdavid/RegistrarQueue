#include <iostream>
#include "Doubly.h"

using namespace std;

template <class T> class RegQueue
{
    public:
        RegQueue(); //default constructor
        ~RegQueue(); //destructor


        void insert(T d);
        T remove();
        bool isEmpty();
        bool isFull();
        T peek();
        int getSize();
        unsigned int size;

        Doubly<T> *myQueue; //array

};

template <class T> //declares template class
RegQueue<T>::RegQueue()
{
    myQueue = new Doubly<T>();
}

template <class T> //declares template class
RegQueue<T>::~RegQueue()
{
    delete myQueue;
}

template <class T> //declares template class
void RegQueue<T>::insert(T d)
{
    myQueue->insertBack(d);
    size++;
}

template <class T> //declares template class
T RegQueue<T>::remove()
{
    myQueue->removeFront();
    size--;
}

template <class T> //declares template class
bool RegQueue<T>::isEmpty()
{
    return size == 0;
}

template <class T> //declares template class
bool RegQueue<T>::isFull()
{
    return myQueue->isFull();
}

template <class T> //declares template class
T RegQueue<T>::peek()
{
    return myQueue->peek();
}

template <class T> //declares template class
int RegQueue<T>::getSize()
{
    return myQueue->getSize();
}
