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
    void push(T _Element);
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
    Node<T> *p = _LinkQueue->head_ptr;
    while(p != nullptr)
    {
        _Ostream << ((p == _LinkQueue->head_ptr)?'\0':' ') << p->value();
        p = p->next();
    }
    return _Ostream;
}

template <typename T>
void LinkQueue<T>::push(T _Element)
{
    if(len == 0)
        initialize(_Element);
    else
    {
        tail_ptr->insert_behind(_Element);
        tail_ptr = tail_ptr->next_ptr;
    }
    ++len;
}

template <typename T>
bool LinkQueue<T>::pop(void)
{
    if(len <= 0)
        return false;
    Node<T> *next = head_ptr->next_ptr;
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
    Node<T> *next = head_ptr->next_ptr;
    delete head_ptr;
    head_ptr = next;
    --len;
    return true;
}

#endif