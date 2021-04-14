#ifndef LINERLINK_H
#define LINERLINK_H

#include <iostream>
#include "Link.h"

template<typename T>
class LinerLink;

template<typename T>
std::ostream& operator<<(std::ostream& _Ostream, LinerLink<T> * _LinerLink);
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class LinerLink : public Link<T>
{

public:
    LinerLink() = default;
    ~LinerLink()
    {
        Link<T>::clear();
    }

    T getElem(link_size_t _Index);
    link_size_t find(T _Element) const;
    void insert(link_size_t _Index, T _Element);
    T remove(link_size_t _Index);
    friend std::ostream& operator<<<T>(std::ostream& _Ostream, LinerLink<T> * _LinerLink);
    using Link<T>::initialize;

private:
    using Link<T>::len;
    using Link<T>::head_ptr;
    using Link<T>::tail_ptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator<<(std::ostream& _Ostream, LinerLink<T> * _LinerLink)
{
    for(Node<T>* p = _LinerLink->head(); p != nullptr; p = p->next())
        _Ostream << ((p == _LinerLink->head())?'\0':' ') << p->value();
    return _Ostream;
}

template <typename T>
void LinerLink<T>::insert(link_size_t _Index, T _Element)
{
    assert((_Index <= len) && "Error: Index out of range\n");
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
T LinerLink<T>::remove(link_size_t _Index)
{
    assert((_Index < len) && "Error: Index out of range\n");
    T res;
    Node<T> *p = (*this)[_Index];
    res = p->value();
    if(p == head_ptr)
        head_ptr = p->next_ptr;
    if(p == tail_ptr)
        tail_ptr = p->prev_ptr;
    delete p;
    --len;
    return res;
}

template <typename T>
T LinerLink<T>::getElem(link_size_t _Index)
{
    return (*this)[_Index]->value();
}

template <typename T>
link_size_t LinerLink<T>::find(T _Element) const
{
    link_size_t cnt = 0;
    Node<T> *p = head_ptr;
    while(p->value() != _Element)
    {
        p = p->next_ptr;
        ++cnt;
    }
    return cnt;
}

#endif