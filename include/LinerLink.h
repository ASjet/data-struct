#ifndef LINERLINK_H
#define LINERLINK_H

#include "Link.h"

template <typename T>
class LinerLink : public Link<T>
{

public:
    LinerLink() = default;
    ~LinerLink() = default;

    void insert(T _Element, link_size_t _Index);
    T getElement(link_size_t _Index);
    void remove(link_size_t _Index);
    using Link<T>::initialize;
    using Link<T>::len;
    using Link<T>::head_ptr;
    using Link<T>::tail_ptr;
};

template <typename T>
void LinerLink<T>::insert(T _Element, link_size_t _Index)
{
    assert((_Index <= len) && ERR_OUT_OF_RANGE);
    if (len == 0)
        initialize(_Element);
    else if (_Index == len)
    {
        tail_ptr->insert_behind(_Element);
        tail_ptr = tail_ptr->next_ptr;
    }
    else
    {
        Node<T> *cur = (*this)[_Index];
        cur->insert_ahead(_Element);
        if (cur == head_ptr)
            head_ptr = cur->prev_ptr;
    }
    ++len;
}

template <typename T>
T LinerLink<T>::getElement(link_size_t _Index)
{
    return (*this)[_Index]->value();
}

template <typename T>
void LinerLink<T>::remove(link_size_t _Index)
{
    assert((_Index < len) && ERR_OUT_OF_RANGE);
    Node<T> *p = (*this)[_Index];
    if(p == head_ptr)
        head_ptr = p->next_ptr;
    if(p == tail_ptr)
        tail_ptr = p->prev_ptr;
    delete p;
    --len;
}

#endif