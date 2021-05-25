#ifndef CIRQUEUE_H
#define CIRQUEUE_H

#include <iostream>
#include "Array.h"

template<typename T>
class CirQueue;

template<typename T>
std::ostream& operator<<(std::ostream& _Ostream, CirQueue<T> * _CirQueue);
//////////////////////////////////////////////////////////////
template <typename T>
class CirQueue : public Array<T>
{
public:
    CirQueue(array_size_t _Size):Array<T>(_Size){}
    ~CirQueue() = default;
    bool push(T _Element);
    bool pop(T &_Destination);
    bool pop(void);
    bool empty(void) const;
    void sort(bool (*comp)(T, T));
    friend std::ostream& operator<<<>(std::ostream& _Ostream, CirQueue<T> * _CirQueue);
private:
    using Array<T>::_len;
    using Array<T>::_base;
    using Array<T>::_size;
    array_size_t head = 0;
    array_size_t tail = 0;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator<<(std::ostream& _Ostream, CirQueue<T> * _CirQueue)
{
    for(array_size_t cnt = 0, i = _CirQueue->head; cnt < _CirQueue->_len; ++cnt, ++i %= _CirQueue->_size)
    {
        _Ostream << ((i == _CirQueue->head)?'\0':' ') << _CirQueue->_base[i];
    }
    return _Ostream;
}

template <typename T>
bool CirQueue<T>::push(T _Element)
{
    if(_len >= _size)
        return false;

    if(_len != 0)
        tail = (tail + 1) % _size;
    _base[tail] = _Element;
    ++_len;
    return true;
}
template <typename T>
bool CirQueue<T>::pop(T &_Destination)
{
    if(_len <= 0)
        return false;

    _Destination = _base[head];
    if(_len != 1)
        head = (head + 1) % _size;
    --_len;
    return true;
}

template <typename T>
bool CirQueue<T>::pop(void)
{
    if(_len <= 0)
        return false;

    if(_len != 1)
        head = (head + 1) % _size;
    --_len;
    return true;
}

template <typename T>
bool CirQueue<T>::empty(void) const
{
    return (_len <= 0);
}

template <typename T>
void CirQueue<T>::sort(bool (*comp)(T, T))
{
    if(_len <= 1)
        return;
    array_size_t p = head, j = 0, k = 0;
    T tmp;
    do
    {
        ++p %= _size;
        j = p;
        tmp = _base[p];
        for(array_size_t i = head; i != p; ++i %= _size)
        {
            if(comp(tmp, _base[i]))
            {
                while(j != i)
                {
                    k = (_size + j - 1) % _size;
                    _base[j] = _base[k];
                    j = k;
                }
                _base[i] = tmp;
                break;
            }
        }
    }
    while(p != tail);
}

#endif