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
class LinkNode
{
public:
    LinkNode()
    {
        body = new T;
        next_ptr = nullptr;
        prev_ptr = nullptr;
    }
    LinkNode(T _Element)
    {
        body = new T;
        *body = _Element;
    }
    ~LinkNode()
    {
        LinkNode<T> * prev = prev_ptr;
        LinkNode<T> * next = next_ptr;
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

    LinkNode<T> * next(void) const;
    LinkNode<T> * prev(void) const;

    bool insert_ahead(T _Element);
    bool insert_behind(T _Element);

    T &value(void);

private:
    LinkNode<T> *next_ptr = nullptr;
    LinkNode<T> *prev_ptr = nullptr;
    T *body = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
LinkNode<T> *LinkNode<T>::next(void) const
{
    return next_ptr;
}

template <typename T>
LinkNode<T> *LinkNode<T>::prev(void) const
{
    return prev_ptr;
}

template <typename T>
T &LinkNode<T>::value(void)
{
    return *body;
}

template <typename T>
bool LinkNode<T>::insert_ahead(T _Element)
{
    LinkNode<T> * p = new LinkNode<T>(_Element);
    if(p == nullptr)
        return false;

    p->next_ptr = this;
    if(prev_ptr != nullptr)
    {
        p->prev_ptr = prev_ptr;
        prev_ptr->next_ptr = p;
    }
    prev_ptr = p;
    return true;
}

template <typename T>
bool LinkNode<T>::insert_behind(T _Element)
{
    LinkNode<T> * p = new LinkNode<T>(_Element);
    if(p == nullptr)
        return false;
    p->prev_ptr = this;
    if(next_ptr != nullptr)
    {
        p->next_ptr = next_ptr;
        next_ptr->prev_ptr = p;
    }
    next_ptr = p;
    return true;
}

#endif