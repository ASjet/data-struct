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

    friend std::ostream& operator<<<T>(std::ostream& _Ostream, LinerLink<T> * _LinerLink);

    T getElem(link_size_t _Index);
    link_size_t find(T _Element) const;
    bool insert(link_size_t _Index, T _Element);
    T remove(link_size_t _Index);
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
    for(LinkNode<T>* p = _LinerLink->head(); p != nullptr; p = p->next())
        _Ostream << ((p == _LinerLink->head())?'\0':' ') << p->value();
    return _Ostream;
}

template <typename T>
bool LinerLink<T>::insert(link_size_t _Index, T _Element)
{
    if(_Index > len || _Index < -1)
        return false;

    if (len == 0)
        return initialize(_Element);
    else if (_Index == len || _Index == -1)
    {
        if(tail_ptr->insert_behind(_Element) == false)
            return false;
        tail_ptr = tail_ptr->next_ptr;
    }
    else
    {
        LinkNode<T> *cur = (*this)[_Index];
        if(cur->insert_ahead(_Element) == false)
            return false;
        if (cur == head_ptr)
            head_ptr = cur->prev_ptr;
    }
    ++len;
    return true;
}

template <typename T>
T LinerLink<T>::remove(link_size_t _Index)
{
    assert((_Index < len) && "Error: Index out of range\n");
    T res;
    LinkNode<T> *p = (*this)[_Index];
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
    LinkNode<T> *p = head_ptr;
    while(p->value() != _Element)
    {
        p = p->next_ptr;
        ++cnt;
    }
    if(cnt == len)
        return -1;
    else
        return cnt;
}

#endif