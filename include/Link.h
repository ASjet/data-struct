#ifndef LINK_H
#define LINK_H

#include <cassert>
typedef int link_size_t;
enum LINK_ERR_T
{
    LINK_ERR,
    LINK_OK
};

template <class T>
class Node
{
public:
    Node()
    {
        body = new T;
    }
    Node(T _Element) : *body(_Element) {}
    ~Node()
    {
        delete body;
    }
    Node<T> *next(void) const;
    Node<T> *prev(void) const;
    T value(void) const;
    void free(void);

private:
    Node<T> *next_ptr = nullptr;
    Node<T> *prev_ptr = nullptr;
    T *body = nullptr;
};

template <class T>
class Link
{
public:
    Link() = default;
    friend class Node<T>;
    friend Node<T> *operator[](link_size_t _Index);
    Node<T> *head(void) const;
    Node<T> *tail(void) const;
    bool empty(void) const;
    link_size_t length(void) const;
    void push(T _Element, link_size_t _Index = length);
    T pop(link_size_t _Index);
    LINK_ERR_T remove(link_size_t _Index);

private:
    Node<T> *head_ptr = nullptr;
    Node<T> *tail_ptr = nullptr;
    link_size_t length = 0;
};

template <class T>
Node<T> *operator[](link_size_t _Index)
{
    if (_Index == length)
        return tail_ptr;
    else
    {
        Node<T> *p = head_ptr;
        for (link_size_t i = 0; i != _Index; ++i)
        {
            assert((p == nullptr) && "Error: Index out of range\n");
            p = p->next();
        }
        return p;
    }
}

#endif