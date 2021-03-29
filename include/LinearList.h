#ifndef LINEARLIST_H
#define LINEARLIST_H
#include <memory>
#include <algorithm>
using len_t = long long;

////////////////////////////////////////////////////////////////////////////////
template <typename ElementType>
class SeqList
{
public:
    SeqList(len_t _ListSize);
    ~SeqList();
    ElementType operator[](len_t _Index);
    // SeqList<ElementType> operator=(const SeqList<ElementType> &_RightValue);
    len_t size(void) const;
    len_t length(void) const;
    bool empty(void) const;
    bool full(void) const;
    len_t find(const ElementType &_Target) const;
    bool push(len_t _Index, const ElementType &element);
    ElementType pop(len_t _Index);
    void sort(bool (*_Comp)(const ElementType &, const ElementType &));

private:
    len_t _Size, _Length;
    // std::allocator<ElementType> _Alloc;
    // std::shared_ptr<ElementType> _Head, _Tail;
    ElementType *_Head, *_Tail;
};

template <typename ElementType>
SeqList<ElementType>::SeqList(len_t _ListSize)
{
    // _Head = _Alloc.allocate(_ListSize);
    // std::shared_ptr<ElementType> _Head(new ElementType[_ListSize]);
    _Head = new ElementType[_ListSize];
    _Tail = _Head + _ListSize + 1;
    _Size = _ListSize;
    _Length = 0;
}

template <typename ElementType>
SeqList<ElementType>::~SeqList()
{
    // _Alloc.deallocate(_Head, _Size);
    delete _Head;
    _Head = nullptr;
    _Tail = nullptr;
}

template <typename ElementType>
ElementType SeqList<ElementType>::operator[](len_t _Index)
{
    return _Head[_Index];
}

// template <typename ElementType>
// SeqList<ElementType>::operator=(const SeqList<ElementType> &_RightValue)
// {

// }

template <typename ElementType>
len_t SeqList<ElementType>::size(void) const
{
    return _Size;
}

template <typename ElementType>
len_t SeqList<ElementType>::length(void) const
{
    return _Length;
}

template <typename ElementType>
bool SeqList<ElementType>::empty(void) const
{
    return !bool(_Length);
}

template <typename ElementType>
bool SeqList<ElementType>::full(void) const
{
    return !bool(_Size - _Length);
}

template <typename ElementType>
len_t SeqList<ElementType>::find(const ElementType &_Target) const
{
    for (auto i = _Head; i != _Tail; ++i)
        if (*i == _Target)
            return int(i - _Head);
    return -1;
}

template <typename ElementType>
bool SeqList<ElementType>::push(len_t _Index, const ElementType &element)
{
    if (_Size - _Length)
    {
        auto p = _Head + _Index;
        ElementType old, rep;
        old = *p;
        *p = element;
        ++p;
        for (int i = 0; i != _Size - _Length; ++i)
        {
            rep = *p;
            *p = old;
            old = rep;
            ++p;
        }
        ++_Length;
        return true;
    }
    else
    {
        return false;
    }
}

template <typename ElementType>
ElementType SeqList<ElementType>::pop(len_t _Index)
{
    auto p = _Head + _Index;
    ElementType poped;
    poped = *p;
    for (int i = 1; i != _Size - _Length; ++i, ++p)
        *p = *(p + 1);
    --_Length;
    return poped;
}

template <typename ElementType>
void SeqList<ElementType>::sort(bool (*_Comp)(const ElementType &, const ElementType &))
{
    std::sort(_Head, _Head + _Length, _Comp);
}

#endif