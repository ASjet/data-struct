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
        _len = _Length;
        sp = _Length;
    }
    ~SeqStack() = default;

    bool push(T _Element);
    bool pop(void);
    bool pop(T * _Destination);
    bool GetTop(T *_Destination) const;

    private:
    using Array<T>::_len;
    using Array<T>::_base;
    using Array<T>::_size;
    array_size_t sp;
};

template<typename T>
bool SeqStack<T>::push(T _Element)
{
    if(_len == _size)
        return false;
    _base[sp] = _Element;
    ++sp;
    ++_len;
    return true;
}

template <typename T>
bool SeqStack<T>::pop(void)
{
    if(_len <= 0)
        return false;
    --sp;
    --_len;
    return true;
}

template <typename T>
bool SeqStack<T>::pop(T * _Destination)
{
    if(_len <= 0)
        return false;
    --sp;
    *_Destination = _base[sp];
    --_len;
    return true;
}

template<typename T>
bool SeqStack<T>::GetTop(T* _Destination) const
{
    if(_len <= 0)
        return false;
    *_Destination = _base[sp];
    return true;
}

#endif