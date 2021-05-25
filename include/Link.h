#ifndef LINK_H
#define LINK_H

#include <cassert>
#include "LinkNode.h"
typedef int link_size_t;
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Link
{
public:
    Link() = default;
    virtual ~Link()
    {
        clear();
    }
    LinkNode<T> *operator[](link_size_t _Index);
    bool initialize(T _Element);
    void initialize(LinkNode<T> *_HeadPtr, LinkNode<T> *_TailPtr, link_size_t _Length);
    bool initializeL(T *_Base, link_size_t _Length);
    bool initializeR(T *_Base, link_size_t _Length);
    void clear(void);
    LinkNode<T> *head(void) const;
    LinkNode<T> *tail(void) const;
    bool empty(void) const;
    link_size_t length(void) const;

protected:
    LinkNode<T> *head_ptr = nullptr;
    LinkNode<T> *tail_ptr = nullptr;
    link_size_t len = 0;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
LinkNode<T> *Link<T>::operator[](link_size_t _Index)
{
    assert((_Index < len) && "Error: Index out of range\n");
    LinkNode<T> *p = head_ptr;
    for (link_size_t i = 0; i != _Index; ++i)
        p = p->next_ptr;
    return p;
}

template <typename T>
bool Link<T>::initialize(T _Element)
{
    clear();
    head_ptr = new LinkNode<T>(_Element);
    if(head_ptr == nullptr)
        return false;
    tail_ptr = head_ptr;
    len = 1;
    return true;
}

template <typename T>
bool Link<T>::initializeL(T *_Base, link_size_t _Length)
{
    clear();
    head_ptr = new LinkNode<T>;
    if(head_ptr == nullptr)
        return false;

    LinkNode<T> *p = head_ptr;
    for (link_size_t i = 0; i < _Length; ++i)
    {
        if (i != 0)
        {
            p->next_ptr = new LinkNode<T>;
            if(p->next_ptr == nullptr)
            {
                clear();
                return false;
            }
            p = p->next_ptr;
        }
        p->value() = _Base[i];
        ++len;
    }
    tail_ptr = p;
    return true;
}

template <typename T>
bool Link<T>::initializeR(T *_Base, link_size_t _Length)
{
    clear();
    tail_ptr = new LinkNode<T>;
    if(tail_ptr == nullptr)
        return false;

    LinkNode<T> *p = tail_ptr;
    for(link_size_t i = 0; i < _Length; ++i)
    {
        if(i != 0)
        {
            p->prev_ptr = new LinkNode<T>;
            if(p->prev_ptr == nullptr)
            {
                clear();
                return false;
            }
            p = p->prev_ptr;
        }
        p->value() = _Base[i];
        ++len;
    }
    head_ptr = p;
    return true;
}

template <typename T>
void Link<T>::initialize(LinkNode<T> *_HeadPtr, LinkNode<T> *_TailPtr, link_size_t _Length)
{
    head_ptr = _HeadPtr;
    tail_ptr = _TailPtr;
    len = _Length;
    head_ptr->prev_ptr = nullptr;
    tail_ptr->next_ptr = nullptr;
}

template <typename T>
void Link<T>::clear()
{
    LinkNode<T> *cur = head_ptr, *next;
    while (len--)
    {
        next = cur->next_ptr;
        delete cur;
        cur = next;
    }
    head_ptr = nullptr;
    tail_ptr = nullptr;
    len = 0;
}

template <typename T>
bool Link<T>::empty(void) const
{
    return (len == 0);
}
template <typename T>
LinkNode<T> *Link<T>::head(void) const
{
    return head_ptr;
}

template <typename T>
LinkNode<T> *Link<T>::tail(void) const
{
    return tail_ptr;
}

template <typename T>
link_size_t Link<T>::length(void) const
{
    return len;
}

#endif
