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

    link_size_t find(T _Element) const;
    bool insert(link_size_t _Index, T _Element);
    T remove(link_size_t _Index);

private:
    using Link<T>::_len;
    using Link<T>::_head_ptr;
    using Link<T>::_tail_ptr;
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
    if(_Index > _len || _Index < -1)
        return false;

    if (_len == 0)
        return Link<T>::initialize(_Element);
    else if (_Index == _len || _Index == -1)
    {
        if(_tail_ptr->insert_behind(_Element) == false)
            return false;
        _tail_ptr = _tail_ptr->_next_ptr;
    }
    else
    {
        LinkNode<T> *cur = (*this)[_Index];
        if(cur->insert_ahead(_Element) == false)
            return false;
        if (cur == _head_ptr)
            _head_ptr = cur->_prev_ptr;
    }
    ++_len;
    return true;
}


template <typename T>
T LinerLink<T>::remove(link_size_t _Index)
{
    T res;
    LinkNode<T> *p = (*this)[_Index];
    res = p->value();
    if(p == _head_ptr)
        _head_ptr = p->_next_ptr;
    if(p == _tail_ptr)
        _tail_ptr = p->_prev_ptr;
    delete p;
    --_len;
    return res;
}


template <typename T>
link_size_t LinerLink<T>::find(T _Element) const
{
    link_size_t cnt = 0;
    LinkNode<T> *p = _head_ptr;
    while(p->value() != _Element)
    {
        p = p->_next_ptr;
        ++cnt;
    }
    if(cnt == _len)
        return -1;
    else
        return cnt;
}


#endif