#ifndef SQLIST_H
#define SQLIST_H

#include <iostream>
#include "Array.h"

template<typename T>
class Sqlist : public Array<T>
{
    public:
    Sqlist() = default;
    Sqlist(array_size_t _Size):Array<T>(_Size){}
    ~Sqlist() = default;

    void disp(void) const;
    T getElem(array_size_t _Index) const;
    array_size_t find(T _Element) const;
    ARRAY_STAT_FLAG insert(array_size_t _Index, T _Element);
    ARRAY_STAT_FLAG remove(array_size_t _Index);
    using Array<T>::move;
    void unique(void);

    private:
    using Array<T>::size;
    using Array<T>::len;
    using Array<T>::base;
    using Array<T>::tail_i;
};

template <typename T>
void Sqlist<T>::disp(void) const
{
    for(array_size_t i = 0; i != len; ++i)
        std::cout << ((i == 0)? '\0' : ' ') << base[i];
    std::cout << std::endl;
}

template <typename T>
T Sqlist<T>::getElem(array_size_t _Index) const
{
    return base[_Index];
}

template <typename T>
array_size_t Sqlist<T>::find(T _Element) const
{
    for(array_size_t i = 0; i != len; ++i)
        if(base[i] == _Element)
            return i;
    return -1;
}

template <typename T>
ARRAY_STAT_FLAG Sqlist<T>::insert(array_size_t _Index, T _Element)
{
    if((len + 1) > size)
        return ARR_ERR;

    move(_Index, tail_i, 1);
    base[_Index] = _Element;
    ++len;
    tail_i = (len == 0) ? 0 : len - 1;
    return ARR_OK;
}

template <typename T>
ARRAY_STAT_FLAG Sqlist<T>::remove(array_size_t _Index)
{
    if(_Index >= len)
        return ARR_ERR;
    else
        move(_Index+1, tail_i, -1);
    --len;
    tail_i = (len == 0) ? 0 : len - 1;
    return ARR_OK;
}

template <typename T>
void Sqlist<T>::unique(void)
{
    T cur;
    for(array_size_t i = 0; i != len; ++i)
    {
        if(i != 0 && cur == base[i])
        {
            move(i+1, tail_i, -1);
            --len;
        }
        else
            cur = base[i];
    }
}
#endif