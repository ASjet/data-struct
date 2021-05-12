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
    bool empty(void) const;
    void sort(bool (*comp)(T, T));
    friend std::ostream& operator<<<>(std::ostream& _Ostream, CirQueue<T> * _CirQueue);
private:
    using Array<T>::len;
    using Array<T>::base;
    using Array<T>::size;
    array_size_t head = 0;
    array_size_t tail = 0;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::ostream& operator<<(std::ostream& _Ostream, CirQueue<T> * _CirQueue)
{
    for(array_size_t cnt = 0, i = _CirQueue->head; cnt < _CirQueue->len; ++cnt, ++i %= _CirQueue->size)
    {
        _Ostream << ((i == _CirQueue->head)?'\0':' ') << _CirQueue->base[i];
    }
    return _Ostream;
}

template <typename T>
bool CirQueue<T>::push(T _Element)
{
    if(len >= size)
        return false;

    if(len != 0)
        tail = (tail + 1) % size;
    base[tail] = _Element;
    ++len;
    return true;
}
template <typename T>
bool CirQueue<T>::pop(T &_Destination)
{
    if(len <= 0)
        return false;

    _Destination = base[head];
    if(len != 1)
        head = (head + 1) % size;
    --len;
    return true;
}

template <typename T>
bool CirQueue<T>::empty(void) const
{
    return (len <= 0);
}

template <typename T>
void CirQueue<T>::sort(bool (*comp)(T, T))
{
    if(len <= 1)
        return;
    array_size_t p = head, j = 0, k = 0;
    T tmp;
    do
    {
        ++p %= size;
        j = p;
        tmp = base[p];
        for(array_size_t i = head; i != p; ++i %= size)
        {
            if(comp(tmp, base[i]))
            {
                while(j != i)
                {
                    k = (size + j - 1) % size;
                    base[j] = base[k];
                    j = k;
                }
                base[i] = tmp;
                break;
            }
        }
    }
    while(p != tail);
}

#endif