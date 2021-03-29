#include "Link.h"

template <class T>
Node<T> *Node<T>::next(void) const
{
    return next_ptr;
}

template <class T>
Node<T> *Node<T>::prev(void) const
{
    return prev_ptr;
}

template <class T>
T Node<T>::value(void) const
{
    return body;
}

template <class T>
void Node<T>::free(void)
{
    Node<T> *cur = this, *next = nullptr;
    while (cur != nullptr)
    {
        next = cur->next_ptr;
        delete cur;
        cur = next;
    }
}
/////////////////////////////////////////////////////////////////////////////////
template <class T>
bool Link<T>::empty(void) const
{
    return (length > 0)? false: true;
}
template <class T>
Node<T> *Link<T>::head(void) const
{
    return head_ptr;
}

template <class T>
Node<T> *Link<T>::tail(void) const
{
    return tail_ptr;
}

template <class T>
link_size_t Link<T>::length(void) const
{
    return length;
}

template <class T>
void Link<T>::push(T _Element, link_size_t _Index)
{
    if(_Index == length)
    {
        tail_ptr->next_ptr = new Node(_Element);
        tail_ptr->next_ptr->prev_ptr = tail_ptr;
        tail_ptr = tail_ptr->next_ptr;
    }
    else
    {
        Node<T> * cur = *this[_Index];
        Node<T> * pre = cur->prev_ptr;
        if(cur == head_ptr)
        {
            head_ptr = new Node(_Element);
            cur->prev_ptr = head_ptr;
            head_ptr->next_ptr = cur;
        }
        else
        {
            pre->next_ptr = new Node(_Element);
            pre->next_ptr->prev_ptr = pre;
            cur->prev_ptr = pre->next_ptr;
            cur->prev_ptr->next_ptr = cur;
        }
    }
}

template <class T>
T Link<T>::pop(link_size_t _Index)
{
    return *this[_Index].value();
}

template <class T>
LINK_ERR_T remove(link_size_t _Index)
{
    Node<T> * p = *this[_Index];
    p->prev_ptr->next_ptr = p->next_ptr;
    p->next_ptr->prev_ptr = p->prev_ptr;
    delete p;
}