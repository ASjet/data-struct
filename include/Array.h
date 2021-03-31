#ifndef ARRAY_H
#define ARRAY_H

#include <cstring>
#include <cassert>

typedef int array_size_t;
enum ARRAY_STAT_FLAG
{
    ARR_OK,
    ARR_ERR
};

template<typename T>
class Array
{
    public:
        Array() = default;
        Array(array_size_t _Size)
        {
            base = new T[_Size];
            size = _Size;
        }
        virtual ~Array()
        {
            delete [] base;
        }
        void clear(void);
        void initialize(array_size_t _Size);
        ARRAY_STAT_FLAG resize(array_size_t _Size);
        bool empty(void) const;
        array_size_t length(void) const;
        // void disp(void) const;
        T& operator[](array_size_t _Index);
        // array_size_t find(T _Element) const;
        ARRAY_STAT_FLAG move(array_size_t _Begin, array_size_t _End, array_size_t _Offset);
        // ARRAY_STAT_FLAG insert(array_size_t _Index, T _Element);
        // ARRAY_STAT_FLAG remove(array_size_t _Index);

    protected:
        array_size_t tail_i = 0;
        array_size_t size = 0;
        array_size_t len = 0;
        T * base = nullptr;


};

template <typename T>
void Array<T>::clear(void)
{
    if(base != nullptr)
        delete [] base;
    base = new T[size];
    len = 0;
    tail_i = 0;
}

template <typename T>
void Array<T>::initialize(array_size_t _Size)
{
    assert((base == nullptr) && "ERROR: Array is not empty");
    base = new T[_Size];
    size = _Size;
    len = 0;
    tail_i = 0;
}

template <typename T>
ARRAY_STAT_FLAG Array<T>::resize(array_size_t _Size)
{
    if(_Size < size)
        return ARR_ERR;
    else
        _Size = size;
    return ARR_OK;
}

template <typename T>
bool Array<T>::empty(void) const
{
    return (len == 0)? true : false;
}

template <typename T>
array_size_t Array<T>::length(void) const
{
    return len;
}

// template <typename T>
// void Array<T>::disp(void) const
// {
//     for(arrar_size_t i = 0; i != len; ++i)
//         std::cout << (i == 0)? " " :"" << base[i];
//     std::cout << std::endl;
// }

template <typename T>
T& Array<T>::operator[](array_size_t _Index)
{
    return base[_Index];
}

// template <typename T>
// array_size_t Array<T>::find(T _Element) const
// {
//     for(array_size_t i = 0; i != len; ++i)
//         if(base[i] == _Element)
//             return i;
//     return -1;
// }

template <typename T>
ARRAY_STAT_FLAG Array<T>::move(array_size_t _Begin, array_size_t _End, array_size_t _Offset)
{
    if((_Begin + _Offset) < 0 || (_End + _Offset) >= size)
        return ARR_ERR;

    if(_Offset == 0)
        return ARR_OK;

    array_size_t seg_len = _End - _Begin + 1;
    if(_Offset > 0)
    {
        for(array_size_t i = 0; i != seg_len; ++i)
            base[_End + _Offset - i] = base[_End - i];
        memset(base+_Begin,0,sizeof(T)*seg_len);

    }
    else
    {
        for(array_size_t i = 0; i != seg_len; ++i)
            base[_Begin + _Offset + i] = base[_Begin + i];
        memset(base+_End,0,sizeof(T)*seg_len);
    }
    return ARR_OK;
}



// template <typename T>
// ARRAY_STAT_FLAG Array<T>::insert(array_size_t _Index, T _Element)
// {
//     if((len + 1) > size)
//         return ARR_ERR;
//     else
//     {
//         move(_Index,len-1,1);
//         base[_Index] = _Element;
//     }
//     return ARR_OK;
// }

// template <typename T>
// ARRAY_STAT_FLAG Array<T>::remove(array_size_t _Index)
// {
//     if(_Index >= len)
//         return ARR_ERR;
//     else
//         move(_Index+1, len-1,-1);
//     return ARR_OK;
// }


#endif