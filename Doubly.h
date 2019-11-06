#include <iostream>
#include "DoublyNode.h"

using namespace std;

// https://stackoverflow.com/questions/49931403/invalid-use-of-template-name-node-without-an-argument-list
// https://stackoverflow.com/questions/12298208/c-get-value-of-a-particular-memory-address
template <class T> class Doubly
{
    public:
        Doubly();
        ~Doubly();

        DoublyNode<T> *front;
        DoublyNode<T> *back;
        unsigned int size;

        // void insertFront(T d);
        void insertBack(T d);
        T removeFront();
        T peek();
        // T removeBack();
        // DoublyNode<T>* remove(T d);
        bool isEmpty();
        bool isFull();
        int getSize();

};

template <class T> //declares template class
Doubly<T>::Doubly()
{
    front = NULL;
    back = NULL;
    size = 0;
}

template <class T> //declares template class
Doubly<T>::~Doubly()
{
    DoublyNode<T> *curr = front;
	while (curr != NULL)
	{
		DoublyNode<T> *garbage = curr;
		curr = curr->next;
	//	(current->prev)->next = NULL;
		curr->prev = NULL;
		delete garbage;
	}
	curr = NULL;
	delete front;
	delete back;

    cout << "object deleted" << endl;
}


template <class T> //declares template class
bool Doubly<T>::isEmpty()
{
    return size == 0;
}

template <class T> //declares template class
bool Doubly<T>::isFull()
{
    return size > 0;
}

template <class T> //declares template class
T Doubly<T>::peek()
{
    return front->data;
}

template <class T> //declares template class
int Doubly<T>::getSize()
{
    return size;
}

template <class T> //declares template class
T Doubly<T>::removeFront()
{
    //check if empty before attempting to remove
    if(size == 0)
    {
        cout << "Cannot remove from empty list" << endl;
        throw -1;
    }

    DoublyNode<T> *ft = front;
    if(front == back)
    {
        back = NULL;
    }
    else
    {
        front->next->prev = NULL;
    }
    T tmp = front->data;
    front = front->next;
    ft->next = NULL;
    delete ft;
    size--;

    return tmp;
}

template <class T> //declares template class
void Doubly<T>::insertBack(T d)
{
    DoublyNode<T> *node = new DoublyNode<T>(d);
    if(size == 0)
    {
        //we have an empty list
        front = node;
    }
    else
    {
        //not an empty list
        node->prev = back;
        back->next = node;
    }
    back = node;
    size++;
}

// template <class T> //declares template class
// T Doubly<T>::removeBack()
// {
//     DoublyNode<T> *bk = back;
//     if(size == 1)
//     {
//         //its the node in the list
//         back = NULL;
//     }
//     else
//     {
//         //we have more than one element in the list
//         back->prev->next = NULL;
//     }
//     back = back->prev;
//     T tmp = back->data;
//     bk->prev = NULL;
//     delete bk;
//     size--;
//
//     return tmp;
//     //make yourself//use removeFront()
// }

// template <class T> //declares template class
// DoublyNode<T>* Doubly<T>::remove(T d)
// {
//     //check if list is not empty before attempting to remove
//     DoublyNode<T> *curr = front;
//
//     while(curr->data != d)
//     {
//         curr = curr->next;
//         if(curr == NULL) //we did not find the value
//         {
//             return NULL;
//         }
//     }
//
//     //if we get to this point it means we found it
//     //lets check if the node is the insert
//     if(curr == front)
//     {
//         front = curr->next;
//     }
//     else
//     {
//         //its not the front
//         curr->prev->next = curr->next;
//     }
//
//     if(curr == back)
//     {
//         back = curr->prev;
//     }
//     else
//     {
//         //its not the back
//         curr->next->prev = curr->prev;
//     }
//
//     curr->next = NULL;
//     curr->prev = NULL;
//     size--;
//
//     return curr;
//     delete curr;
//
// }

// template <class T> //declares template class
// void Doubly<T>::insertFront(T d)
// {
//     DoublyNode<T> *node = new DoublyNode<T>(d);
//     if(size == 0)
//     {
//         back = node;
//     }
//     else
//     {
//         //not an empty list
//         node->next = front;
//         front->prev = node;
//     }
//     front = node;
//     size++;
// }
