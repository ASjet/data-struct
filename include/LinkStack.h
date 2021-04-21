#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Link.h"

template<typename T>
class LinkStack : public Link<T>
{
    public:
    LinkStack() = default;
    ~LinkStack(){
        Link<T>::clear();
    }

    void push(T _Element);
    bool pop(void);
    bool pop(T * _Destination);
    bool GetTop(T * _Destination) const;
    using Link<T>::initialize;

    private:
    using Link<T>::len;
    using Link<T>::head_ptr;
    using Link<T>::tail_ptr;
};

template <typename T>
void LinkStack<T>::push(T _Element)
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
bool LinkStack<T>::pop(void)
{
    if(len <= 0)
        return false;
    Node<T> *pre = tail_ptr->prev_ptr;
    if (pre == nullptr)
        head_ptr = pre;
    delete tail_ptr;
    tail_ptr = pre;
    --len;
    return true;
}

template <typename T>
bool LinkStack<T>::pop(T * _Destination)
{
    if(len <= 0)
        return false;
    *_Destination = tail_ptr->value();
    Node<T> *pre = tail_ptr->prev_ptr;
    if (pre == nullptr)
        head_ptr = pre;
    delete tail_ptr;
    tail_ptr = pre;
    --len;
    return true;
}

template <typename T>
bool LinkStack<T>::GetTop(T * _Destination) const
{
    if(len <= 0)
        return false;
    else
        *_Destination = tail_ptr->value();
    return true;
}

#endif