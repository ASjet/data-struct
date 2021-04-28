#ifndef SHARESTACK_H
#define SHARESTACK_H

#include "Array.h"
enum STACK_FLAG
{
    LEFT_STACK,
    RIGHT_STACK
};

template <typename T>
class ShareStack : public Array<T>
{
public:
    ShareStack() = default;
    ShareStack(array_size_t _Size) : Array<T>(_Size) {}
    ShareStack(T *_Base, array_size_t _Length)
    {
        for (array_size_t i = 0; i < _Length; ++i)
            push(_Base[i]);
    }
    ~ShareStack() = default;

    void init(array_size_t _Size);
    void clear(STACK_FLAG _Flag);
    bool push(T _Element, STACK_FLAG _Flag);
    bool pop(STACK_FLAG _Flag);
    bool pop(T *_Destination, STACK_FLAG _Flag);
    bool GetTop(T *_Destination, STACK_FLAG _Flag) const;
    bool isEmpty(STACK_FLAG _Flag) const;
    bool isFull(void) const;

private:
    using Array<T>::base;
    using Array<T>::size;
    array_size_t spl;
    array_size_t spr;
    array_size_t lenl;
    array_size_t lenr;
};

template <typename T>
void ShareStack<T>::init(array_size_t _Size)
{
    Array<T>::initialize(_Size);
    spl = 0;
    spr = size - 1;
    lenl = 0;
    lenr = 0;
}

template <typename T>
void ShareStack<T>::clear(STACK_FLAG _Flag)
{
    if (_Flag == RIGHT_STACK)
    {
        spr = size - 1;
        lenr = 0;
    }
    else
    {
        spl = 0;
        lenl = 0;
    }
}

template <typename T>
bool ShareStack<T>::push(T _Element, STACK_FLAG _Flag)
{
    if (isFull())
        return false;

    if (_Flag == RIGHT_STACK)
    {
        base[spr] = _Element;
        --spr;
        ++lenr;
    }
    else
    {
        base[spl] = _Element;
        ++spl;
        ++lenl;
    }
    return true;
}

template <typename T>
bool ShareStack<T>::pop(STACK_FLAG _Flag)
{
    if (isEmpty(_Flag))
        return false;

    if (_Flag == RIGHT_STACK)
    {
        ++spr;
        --lenr;
    }
    else
    {
        --spl;
        --lenl;
    }
    return true;
}

template <typename T>
bool ShareStack<T>::pop(T *_Destination, STACK_FLAG _Flag)
{
    if (pop(_Flag) == false)
        return false;

    int sp = (_Flag == RIGHT_STACK) ? spr : spl;
    *_Destination = base[sp];
    return true;
}

template <typename T>
bool ShareStack<T>::GetTop(T *_Destination, STACK_FLAG _Flag) const
{
    if (isEmpty(_Flag))
        return false;

    if(_Flag == RIGHT_STACK)
        *_Destination = base[spr+1];
    else
        *_Destination = base[spl-1];
    return true;
}

template <typename T>
bool ShareStack<T>::isEmpty(STACK_FLAG _FLAG) const
{
    int len = (_FLAG == RIGHT_STACK) ? lenr : lenl;
    return (len == 0);
}

template <typename T>
bool ShareStack<T>::isFull(void) const
{
    return (spl > spr);
}

#endif