#ifndef LINK_H
#define LINK_H

#include <cassert>
typedef int link_size_t;
enum LINK_STAT_FLAG
{
    LINK_OK,
    LINK_ERR
};
#define ERR_OUT_OF_RANGE "Error: Index out of range\n"
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Link;

template <typename T>
class Node;
template <typename T>
class Node
{
public:
    Node()
    {
        body = new T;
        next_ptr = nullptr;
        prev_ptr = nullptr;
    }
    Node(T _Element)
    {
        body = new T;
        *body = _Element;
    }
    ~Node()
    {
        Node<T> * prev = prev_ptr;
        Node<T> * next = next_ptr;
        if(next != nullptr)
            next->prev_ptr = prev;
        if(prev != nullptr)
            prev->next_ptr = next;
        delete body;
    }
    Node<T> *next(void) const;
    Node<T> *prev(void) const;
    T &value(void);
    void insert_ahead(T _Element);
    void insert_behind(T _Element);

    Node<T> *next_ptr = nullptr;
    Node<T> *prev_ptr = nullptr;

private:
    T *body = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
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
void Node<T>::insert_ahead(T _Element)
{
    Node<T> * p = new Node<T>(_Element);
    p->next_ptr = this;
    if(prev_ptr != nullptr)
    {
        p->prev_ptr = prev_ptr;
        prev_ptr->next_ptr = p;
    }
    prev_ptr = p;
}

template <typename T>
void Node<T>::insert_behind(T _Element)
{
    Node<T> * p = new Node<T>(_Element);
    p->prev_ptr = this;
    if(next_ptr != nullptr)
    {
        p->next_ptr = next_ptr;
        next_ptr->prev_ptr = p;
    }
    next_ptr = p;
}
/////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Link
{
public:
    Link() = default;
    virtual ~Link(){
        Node<T> * cur = head_ptr, *next;
        while(cur != nullptr)
        {
            next = cur->next_ptr;
            delete cur;
            cur = next;
        }
    }
    Node<T> *operator[](link_size_t _Index);
    void initialize(T _Element);
    Node<T> *head(void) const;
    Node<T> *tail(void) const;
    bool empty(void) const;
    link_size_t length(void) const;

    void push(T _Element);
    T pop(void);

protected:
    Node<T> *head_ptr = nullptr;
    Node<T> *tail_ptr = nullptr;
    link_size_t len = 0;
};
////////////////////////////////////////////////////////////////////////////////
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
void Link<T>::initialize(T _Element)
{
    head_ptr = new Node<T>(_Element);
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
    Node<T> * pre = tail_ptr->prev_ptr;
    if(pre == nullptr)
        head_ptr = pre;
    delete tail_ptr;
    tail_ptr = pre;
    --len;
    return ret;
}

#endif
