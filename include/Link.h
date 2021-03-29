#ifndef LINK_H
#define LINK_H

#include <cassert>
typedef int link_size_t;
enum LINK_STAT_FLAG
{
    LINK_ERR,
    LINK_OK
};
const char *ERR_OUT_OF_RANGE = "Error: Index out of range\n";

template <typename T>
class Link;
template <typename T>
class Node
{
public:
    Node()
    {
        body = new T;
    }
    Node(T _Element)
    {
        body = new T;
        *body = _Element;
    }
    ~Node()
    {
        delete body;
    }
    friend class Link<T>;
    Node<T> *next(void) const;
    Node<T> *prev(void) const;
    T &value(void);
    void free(void);

private:
    Node<T> *next_ptr = nullptr;
    Node<T> *prev_ptr = nullptr;
    T *body = nullptr;
};

template <typename T>
Node<T> *Node<T>::next(void) const
{
    return next_ptr;
}

template <typename T>
Node<T> *Node<T>::prev(void) const
{
    return prev_ptr;
}

template <typename T>
T &Node<T>::value(void)
{
    return *body;
}

template <typename T>
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
template <typename T>
class Link
{
public:
    Link() = default;
    friend class Node<T>;
    Node<T> *operator[](link_size_t _Index);
    void initialize(void);
    Node<T> *head(void) const;
    Node<T> *tail(void) const;
    bool empty(void) const;
    link_size_t length(void) const;
    void insert(T _Element, link_size_t _Index);
    T getElement(link_size_t _Index);
    void push(T _Element);
    T pop(void);
    void remove(link_size_t _Index);

private:
    Node<T> *head_ptr = nullptr;
    Node<T> *tail_ptr = nullptr;
    link_size_t len = 0;
};

template <typename T>
Node<T> *Link<T>::operator[](link_size_t _Index)
{
    assert((_Index < len) && ERR_OUT_OF_RANGE);
    Node<T> *p = head_ptr;
    for (link_size_t i = 0; i != _Index; ++i)
        p = p->next();
    return p;
}

template <typename T>
void Link<T>::initialize(void)
{
    head_ptr = new Node<T>;
    tail_ptr = head_ptr;
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
void Link<T>::insert(T _Element, link_size_t _Index)
{
    assert((_Index <= len) && ERR_OUT_OF_RANGE);
    if (len == 0)
    {
        initialize();
        tail_ptr->value() = _Element;
    }
    else if (_Index == len)
    {
        tail_ptr->next_ptr = new Node<T>(_Element);
        tail_ptr->next_ptr->prev_ptr = tail_ptr;
        tail_ptr = tail_ptr->next_ptr;
    }
    else
    {
        Node<T> *cur = (*this)[_Index];
        Node<T> *pre = cur->prev_ptr;
        if (cur == head_ptr)
        {
            head_ptr = new Node<T>(_Element);
            cur->prev_ptr = head_ptr;
            head_ptr->next_ptr = cur;
        }
        else
        {
            pre->next_ptr = new Node<T>(_Element);
            pre->next_ptr->prev_ptr = pre;
            cur->prev_ptr = pre->next_ptr;
            cur->prev_ptr->next_ptr = cur;
        }
    }
    ++len;
}

template <typename T>
T Link<T>::getElement(link_size_t _Index)
{
    return (*this)[_Index]->value();
}

template <typename T>
void Link<T>::push(T _Element)
{
    if (len == 0)
    {
        initialize();
        tail_ptr->value() = _Element;
    }
    else
    {
        tail_ptr->next_ptr = new Node<T>(_Element);
        tail_ptr->next_ptr->prev_ptr = tail_ptr;
        tail_ptr = tail_ptr->next_ptr;
    }
    ++len;
}

template <typename T>
T Link<T>::pop(void)
{
    assert((len > 0) && "There is no element to pop in current link");
    T ret = tail_ptr->value();
    if (len == 1)
    {
        delete tail_ptr;
        head_ptr = nullptr;
        tail_ptr = nullptr;
    }
    else
    {
        tail_ptr = tail_ptr->prev_ptr;
        delete tail_ptr->next_ptr;
        tail_ptr->next_ptr = nullptr;
    }
    --len;
    return ret;
}

template <typename T>
void Link<T>::remove(link_size_t _Index)
{
    assert((_Index < len) && ERR_OUT_OF_RANGE);
    Node<T> *p = (*this)[_Index];
    if(len == 1)
    {
        delete tail_ptr;
        head_ptr = nullptr;
        tail_ptr = nullptr;
    }
    else if(p == head_ptr && p != tail_ptr)
    {
        head_ptr->next_ptr->prev_ptr = nullptr;
        head_ptr = head_ptr->next_ptr;
        delete p;
    }
    else if (p == tail_ptr && p != head_ptr)
    {
        tail_ptr->prev_ptr->next_ptr = nullptr;
        tail_ptr = tail_ptr->prev_ptr;
        delete p;
    }
    else
    {
        p->prev_ptr->next_ptr = p->next_ptr;
        p->next_ptr->prev_ptr = p->prev_ptr;
        delete p;
    }
    --len;
}

#endif