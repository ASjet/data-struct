#ifndef EDGENODE_H
#define EDGENODE_H

#include "VertexNode.h"

template <typename W, typename E>
class EdgeNode
{
    public:
    EdgeNode() = default;
    EdgeNode(VertexNode<W, E> * _In, VertexNode<W, E> * _Out, W _Weight, EdgeNode<W, E> * _Prev)
    {
        _in = _In;
        _out = _Out;
        _weight = _Weight;
        _prev = _Prev;
        _prev->_next = this;
    }
    ~EdgeNode()
    {
        if(_prev != nullptr)
            _prev->_next = _next;
        if(_next != nullptr)
            _next->_prev = _prev;
    }
    private:
    VertexNode<W, E> * _in = nullptr;
    VertexNode<W, E> * _out = nullptr;
    EdgeNode<W, E> * _prev = nullptr;
    EdgeNode<W, E> * _next = nullptr;
    E _weight;
};


#endif