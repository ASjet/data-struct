#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <iostream>
#include "Link.h"

template<typename T>
class LinkQueue;

template<typename T>
std::ostream& operator<<(std::ostream& _Ostream, LinkQueue<T> * _LinkQueue);
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class LinkQueue : public Link<T>
{
    public:
    LinkQueue() = default;
    ~LinkQueue(){
        Link<T>::clear();
    }
    using Link<T>::initialize;
    bool push(T _Element);
    bool pop(T &_Destination);
    bool pop(void);
    friend std::ostream& operator<<<>(std::ostream& _Ostream, LinkQueue<T> * _LinkQueue);
private:
    using Link<T>::len;
    using Link<T>::head_ptr;
    using Link<T>::tail_ptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator<<(std::ostream& _Ostream, LinkQueue<T> * _LinkQueue)
{
    LinkNode<T> *p = _LinkQueue->head_ptr;
    while(p != nullptr)
    {
        _Ostream << ((p == _LinkQueue->head_ptr)?'\0':' ') << p->value();
        p = p->next();
    }
    return _Ostream;
}

template <typename T>
bool LinkQueue<T>::push(T _Element)
{
    if(len == 0)
        return initialize(_Element);
    else
    {
        if(tail_ptr->insert_behind(_Element))
            tail_ptr = tail_ptr->next_ptr;
        else
            return false;
    }
    ++len;
    return true;
}

template <typename T>
bool LinkQueue<T>::pop(void)
{
    if(len <= 0)
        return false;
    LinkNode<T> *next = head_ptr->next_ptr;
    delete head_ptr;
    head_ptr = next;
    --len;
    return true;
}

template <typename T>
bool LinkQueue<T>::pop(T &_Destination)
{
    if(len <= 0)
        return false;
    _Destination = head_ptr->value();
    LinkNode<T> *next = head_ptr->next_ptr;
    delete head_ptr;
    head_ptr = next;
    --len;
    return true;
}

#endif