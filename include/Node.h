#ifndef NODE_H
#define NODE_H

////////////////////////////////////////////////////////////////////////////////
template <typename T> class Link;
template <typename T> class LinerLink;
template <typename T> class CLink;
template <typename T> class LinkStack;
template <typename T> class LinkQueue;
////////////////////////////////////////////////////////////////////////////////
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
    friend class Link<T>;
    friend class LinerLink<T>;
    friend class CLink<T>;
    friend class LinkStack<T>;
    friend class LinkQueue<T>;

    Node<T> * next(void) const;
    Node<T> * prev(void) const;

    void insert_ahead(T _Element);
    void insert_behind(T _Element);

    T &value(void);

private:
    Node<T> *next_ptr = nullptr;
    Node<T> *prev_ptr = nullptr;
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

#endif