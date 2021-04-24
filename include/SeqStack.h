#ifndef SEQSTACK_H
#define SEQSTACK_H

#include "Array.h"

template<typename T>
class SeqStack : public Array<T>
{
    public:
    SeqStack() = default;
    SeqStack(array_size_t _Size):Array<T>(_Size){}
    SeqStack(T *_Base, array_size_t _Length)
    {
        for(array_size_t i = 0; i < _Length; ++i)
            push(_Base[i]);
        len = _Length;
        sp = _Length;
    }
    ~SeqStack() = default;

    bool push(T _Element);
    bool pop(void);
    bool pop(T * _Destination);
    bool GetTop(T *_Destination) const;

    private:
    using Array<T>::len;
    using Array<T>::base;
    using Array<T>::size;
    array_size_t sp;
};

template<typename T>
bool SeqStack<T>::push(T _Element)
{
    if(len == size)
        return false;
    base[sp] = _Element;
    ++sp;
    ++len;
    return true;
}

template <typename T>
bool SeqStack<T>::pop(void)
{
    if(len <= 0)
        return false;
    --sp;
    --len;
    return true;
}

template <typename T>
bool SeqStack<T>::pop(T * _Destination)
{
    if(len <= 0)
        return false;
    --sp;
    *_Destination = base[sp];
    --len;
    return true;
}

template<typename T>
bool SeqStack<T>::GetTop(T* _Destination) const
{
    if(len <= 0)
        return false;
    *_Destination = base[sp];
    return true;
}

#endif