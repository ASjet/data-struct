#ifndef VERTEXNODE_H
#define VERTEXNODE_H

#include <cassert>
#include "EdgeNode.h"

template <typename W, typename E>
class VertexNode
{
public:
    VertexNode() = default;
    VertexNode(E _Value, VertexNode<W, E> *_Prev)
    {
        _value = _Value;
        _prev = _Prev;
        if(_prev != nullptr)
            _prev->_next = this;

    }
    ~VertexNode()
    {
        if (_prev != nullptr)
            _prev->_next = _next;
        if (_next != nullptr)
            _next->_prev = _prev;
        EdgeNode<W, E> *cur = _edge_tail, *pre = nullptr;
        while (cur != nullptr)
        {
            pre = cur->_prev;
            delete cur;
            cur = pre;
        }
    }
    VertexNode<W, E> * operator[](graph_size_t _Index);
    bool setNeighbor(VertexNode<W, E> * _Head, W * _Edges, graph_size_t _Length);
    VertexNode<W, E> *firstNeighbor(void);
    VertexNode<W, E> *nextNeighbor(void);

private:
    VertexNode<W, E> *_prev = nullptr;
    VertexNode<W, E> *_next = nullptr;
    E _value;
    EdgeNode<W, E> *_edge_head = nullptr;
    EdgeNode<W, E> *_edge_tail = nullptr;
    EdgeNode<W, E> *_sel = 0;
};
////////////////////////////////////////////////////////////////////////////////
template <typename W, typename E>
VertexNode<W, E> * VertexNode<W, E>::operator[](graph_size_t _Index)
{
    VertexNode<W, E> * p = this;
    for(graph_size_t i = 0; i < _Index; ++i)
        p = p->_next;
    return p;
}


template <typename W, typename E>
VertexNode<W, E> *VertexNode<W, E>::firstNeighbor(void)
{
    _sel = _edge_head;
    return _sel->out();
}


template <typename W, typename E>
VertexNode<W, E> * VertexNode<W,E>::nextNeighbor(void)
{
    _sel = _sel->_next;
    return _sel->out();
}


template <typename W, typename E>
bool VertexNode<W, E>::setNeighbor(VertexNode<W, E> * _Head, W * _Edges, graph_size_t _Length)
{
    EdgeNode<W, E> *p = nullptr;
    for (graph_size_t i = 0; i < _Length; ++i)
    {
        p = new EdgeNode<W, E>(this, _Head[i], _Edges[i], _edge_tail);
        return false;
        if(_edge_head == nullptr)
            _edge_head = p;
        _edge_tail = p;
    }
    return true;
}


#endif