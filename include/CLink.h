#ifndef CLink_H
#define CLink_H

#include <iostream>
#include "Link.h"
typedef int clink_size_t;

template <typename T>
class CLink;

template <typename T>
class CLink : public Link<T>
{

public:
    CLink() = default;
    ~CLink()
    {
        Link<T>::clear();
    }

    void initialize(T _Element);
    void initializeL(T *_Base, link_size_t _Length);
    void initializeR(T *_Base, link_size_t _Length);
    using Link<T>::clear;
    T getElem(link_size_t _Index);
    void disp(bool _Inverse) const;
    link_size_t find(T _Element) const;
    void insert(link_size_t _Index, T _Element);
    T remove(link_size_t _Index);

private:
    using Link<T>::tail;
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
        std::cout << ((p == head_ptr) ? '\0' : ' ') << p->value();
        p = (_Inverse) ? p->prev_ptr : p->next_ptr;
    } while (p != head_ptr);
    std::cout << std::endl;
}

template <typename T>
void CLink<T>::initialize(T _Element)
{
    clear();
    head_ptr = new Node<T>(_Element);
    head_ptr->next_ptr = head_ptr;
    head_ptr->prev_ptr = head_ptr;
}

template <typename T>
void CLink<T>::initializeL(T *_Base, link_size_t _Length)
{
    clear();
    head_ptr = new Node<T>;
    Node<T> *p = head_ptr;
    for (link_size_t i = 0; i < _Length; ++i)
    {
        if(i != 0)
        {
            p->prev_ptr = new Node<T>;
            p->prev_ptr->next_ptr = p;
            p = p->prev_ptr;
        }
        ++len;
        p->value() = _Base[i];
    }
    p->prev_ptr = head_ptr;
    head_ptr->next_ptr = p;
    head_ptr = p;
}

template <typename T>
void CLink<T>::initializeR(T *_Base, link_size_t _Length)
{
    clear();
    head_ptr = new Node<T>;
    Node<T> *p = head_ptr;
    for (link_size_t i = 0; i < _Length; ++i)
    {
        if (i != 0)
        {
            p->next_ptr = new Node<T>;
            p->next_ptr->prev_ptr = p;
            p = p->next_ptr;
        }
        ++len;
        p->value() = _Base[i];
    }
    p->next_ptr = head_ptr;
    head_ptr->prev_ptr = p;
}

template <typename T>
void CLink<T>::insert(link_size_t _Index, T _Element)
{
    assert((_Index <= len) && "Error: Index out of range\n");
    if (len == 0)
        initialize(_Element);
    else if (_Index == len)
    {
        head_ptr->prev_ptr->next_ptr = new Node<T>(_Element);
        head_ptr->prev_ptr->next_ptr->next_ptr = head_ptr;
        head_ptr->prev_ptr = head_ptr->prev_ptr->next_ptr;
    }
    else
    {
        Node<T> *cur = (*this)[_Index];
        cur->next_ptr->prev_ptr = new Node<T>(_Element);
        cur->next_ptr->prev_ptr->prev_ptr = cur;
        cur->next_ptr = cur->next_ptr->prev_ptr;
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