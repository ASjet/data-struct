#ifndef GRAPHLNK_H
#define GRAPHLNK_H

#include <iostream>
#include <cassert>
#include "Graph.h"
#include "VertexNode.h"
#include "EdgeNode.h"

template <typename W, typename E>
class GraphLnk;

template <typename W, typename E>
std::ostream& operator<<(std::ostream& _Ostream, GraphLnk<W, E> _GraphLnk);

template <typename W, typename E>
class GraphLnk : public Graph
{
    public:
    GraphLnk() = default;
    GraphLnk(W ** _EdgeMat, E * _Elements, graph_size_t _VertexCount, graph_size_t _EdgeCount)
    {
        _vc = _VertexCount;
        _ev = _EdgeCount;
        VertexNode<W ,E> * p = nullptr;
        for(graph_size_t i = 0; i < _vc; ++i)
        {
            p = new VertexNode<W, E>(_Elements[i], p);
            assert((p != nullptr) && "MEMORY ALLOC ERROR.");
            if(_head == nullptr)
                _head = p;
        }
        p = _head;
        for(graph_size_t i = 0; i < _vc; ++i)
        {
            p->setNeighbor(_head, _EdgeMat[i], _vc);
            p = p->_next;
        }
    }
    private:
    graph_size_t _vc = 0;
    graph_size_t _ec = 0;
    VertexNode<W, E> * _head = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename W, typename E>
std::ostream& operator<<(std::ostream& _Ostream, GraphLnk<W, E> _GraphLnk)
{
    VertexNode<W, E> * p = _GraphLnk._head;
    EdgeNode<W, E> * e = nullptr;
    while(p != nullptr)
    {
        _Ostream << p->_value << ":\t";
        e = p->_edge_head;
        while(e != nullptr)
        {
            _Ostream << e->_out->_value << '[' << e->_weight << "]-> ";
            e = e->_next;
        }
        _Ostream << '^' << std::endl;
    }
    return _Ostream;
}


#endif