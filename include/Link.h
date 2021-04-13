#ifndef LINK_H
#define LINK_H

#include <cassert>
#include "Node.h"
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
    Node<T> *operator[](link_size_t _Index);
    void initialize(T _Element);
    void initialize(Node<T> *_HeadPtr, Node<T> *_TailPtr, link_size_t _Length);
    void initializeL(T *_Base, link_size_t _Length);
    void initializeR(T *_Base, link_size_t _Length);
    void clear(void);
    Node<T> *head(void) const;
    Node<T> *tail(void) const;
    bool empty(void) const;
    link_size_t length(void) const;

protected:
    void push(T _Element);
    T pop(void);

    Node<T> *head_ptr = nullptr;
    Node<T> *tail_ptr = nullptr;
    link_size_t len = 0;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
Node<T> *Link<T>::operator[](link_size_t _Index)
{
    assert((_Index < len) && "Error: Index out of range\n");
    Node<T> *p = head_ptr;
    for (link_size_t i = 0; i != _Index; ++i)
        p = p->next_ptr;
    return p;
}

template <typename T>
void Link<T>::initialize(T _Element)
{
    clear();
    head_ptr = new Node<T>(_Element);
    tail_ptr = head_ptr;
}

template <typename T>
void Link<T>::initializeL(T *_Base, link_size_t _Length)
{
    clear();
    Node<T> *p = head_ptr;
    for (link_size_t i = 0; i < _Length; ++i)
    {
        if (i != 0)
        {
            p->next_ptr = new Node<T>;
            p = p->next_ptr;
        }
        p->value() = _Base[i];
        ++len;
    }
    tail_ptr = p;
}

template <typename T>
void Link<T>::initializeR(T *_Base, link_size_t _Length)
{
    clear();
    Node<T> *p = tail_ptr;
    for(link_size_t i = 0; i < _Length; ++i)
    {
        if(i != 0)
        {
            p->prev_ptr = new Node<T>;
            p = p->prev_ptr;
        }
        p->value() = _Base[i];
        ++len;
    }
    head_ptr = p;
}

template <typename T>
void Link<T>::initialize(Node<T> *_HeadPtr, Node<T> *_TailPtr, link_size_t _Length)
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
    Node<T> *cur = head_ptr, *next;
    while (cur != nullptr)
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
    return (len > 0) ? false : true;
}
template <typename T>
Node<T> *Link<T>::head(void) const
{
    return head_ptr;
}

template <typename T>
Node<T> *Link<T>::tail(void) const
{
    return tail_ptr;
}

template <typename T>
link_size_t Link<T>::length(void) const
{
    return len;
}

template <typename T>
void Link<T>::push(T _Element)
{
    if (len == 0)
        initialize(_Element);
    else
    {
        tail_ptr->insert_behind(_Element);
        tail_ptr = tail_ptr->next_ptr;
    }
    ++len;
}

template <typename T>
T Link<T>::pop(void)
{
    assert((len > 0) && "There is no element to pop in current link");
    T ret = tail_ptr->value();
    Node<T> *pre = tail_ptr->prev_ptr;
    if (pre == nullptr)
        head_ptr = pre;
    delete tail_ptr;
    tail_ptr = pre;
    --len;
    return ret;
}

#endif
