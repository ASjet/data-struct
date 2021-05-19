#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#include "LinkStack.h"

template<typename T>
class StackQueue
{
    public:
    StackQueue(){
        s1 = new LinkStack<int>;
        s2 = new LinkStack<int>;
    }
    ~StackQueue(){
        delete s1;
        delete s2;
    }
    void push(T _Element);
    bool pop(void);
    bool pop(T &_Destination);
    bool empty(void) const;

    private:
    void swap(void);
    link_size_t len = 0;
    LinkStack<T> * s1, *s2;
};
////////////////////////////////////////////////////////////////////////////////
template<typename T>
void StackQueue<T>::swap(void)
{
    T tmp;
    while(!s1->empty())
    {
        s1->pop(tmp);
        s2->push(tmp);
    }
}


template<typename T>
void StackQueue<T>::push(T _Element)
{
    s1->push(_Element);
    ++len;
}

template<typename T>
bool StackQueue<T>::pop(void)
{
    if(s2->empty())
        swap();
    --len;
    return s2->pop();
}

template<typename T>
bool StackQueue<T>::pop(T &_Destination)
{
    if(s2->empty())
        swap();
    --len;
    return s2->pop(_Destination);
}

template<typename T>
bool StackQueue<T>::empty(void) const
{
    return (len == 0);
}


#endif