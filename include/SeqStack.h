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
    }
    ~SeqStack() = default;

    void push(T _Element);
    T pop(void);
    T GetTop(void) const;

    private:
    using Array<T>::len;
    using Array<T>::base;
    using Array<T>::size;
    array_size_t sp;
};

template<typename T>
void SeqStack<T>::push(T _Element)
{
    ++sp;
    assert((sp < size)&&"Error: Stack Overflow!");
    base[sp] = _Element;
    ++len;
}

template <typename T>
T SeqStack<T>::pop(void)
{
    assert((len > 0)&&"Error: Stack is empty!");
    --len;
    return base[sp--];
}

template<typename T>
T SeqStack<T>::GetTop(void) const
{
    assert((len > 0)&&"Error: Stack empty!");
    return base[sp];
}

#endif