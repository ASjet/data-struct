#ifndef CLink_H
#define CLink_H

#include <iostream>
#include "Link.h"

template <typename T>
class CLink;

template <typename T>
class CLink : public Link<T>
{

public:
    CLink() = default;
    ~CLink() = default;

    void initializeL(T *_Base, link_size_t _Length);
    void initializeR(T *_Base, link_size_t _Length);
    using Link<T>::clear;
    T getElem(link_size_t _Index);
    void disp(bool _Inverse) const;
    link_size_t find(T _Element) const;
    void insert(link_size_t _Index, T _Element);
    T remove(link_size_t _Index);

private:
    using Link<T>::len;
    using Link<T>::head_ptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CLink<T>::disp(bool _Inverse) const
{
    Node<T> *p = head_ptr;
    do
    {
        std::cout << p->value() << ((p == head_ptr) ? '\0' : ' ') << std::endl;
        p = (_Inverse) ? p->prev_ptr : p->next_ptr;
    } while (p != head_ptr);
}

template <typename T>
void CLink<T>::initializeL(T *_Base, link_size_t _Length)
{
    clear();
    Node<T> *p = head_ptr;
    for (link_size_t i = 0; i < _Length; ++i)
    {
        if (i != 0)
        {
            p->next_ptr = new Node<T>;
            p = p->next_ptr;
        }
        p->value() = _Base[i];
        ++len;
    }
    p->prev_ptr = head_ptr;
}

template <typename T>
void CLink<T>::initializeR(T *_Base, link_size_t _Length)
{
    clear();
    Node<T> *p = head_ptr;
    for (link_size_t i = 0; i < _Length; ++i)
    {
        if (i != 0)
        {
            p->prev_ptr = new Node<T>;
            p = p->prev_ptr;
        }
        p->value() = _Base[i];
        ++len;
    }
    p->next_ptr = head_ptr;
}

template <typename T>
void CLink<T>::insert(link_size_t _Index, T _Element)
{
    assert((_Index <= len) && "Error: Index out of range\n");
    if (len == 0)
        initialize(_Element);
    else if (_Index == len)
    {
        head_ptr->insert_ahead(_Element);
        head_ptr = head_ptr->prev_ptr;
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
T CLink<T>::remove(link_size_t _Index)
{
    assert((_Index < len) && "Error: Index out of range\n");
    T res;
    Node<T> *p = (*this)[_Index];
    res = p->value();
    if (p == head_ptr)
    {
        head_ptr = p->next_ptr;
        head_ptr->prev_ptr = p->prev_ptr;
    }
    delete p;
    --len;
    return res;
}

template <typename T>
T CLink<T>::getElem(link_size_t _Index)
{
    return (*this)[_Index]->value();
}

template <typename T>
link_size_t CLink<T>::find(T _Element) const
{
    link_size_t cnt = 0;
    Node<T> *p = head_ptr;
    while (p->value() != _Element)
    {
        p = p->next_ptr;
        ++cnt;
    }
    return cnt;
}

#endif