#ifndef GRAPHMAT_H
#define GRAPHMAT_H

#include <iostream>
#include <string>
#include "Graph.h"
#define INF -1

template <typename W, typename E>
class GraphMat;
template <typename W, typename E>
class GraphLnk;
#include "GraphLnk.h"
template <typename W, typename E>
std::ostream &operator<<(std::ostream &_Ostream, GraphMat<W, E>& _GraphMat);

template <typename W, typename E>
class GraphMat
{
public:
    GraphMat() = default;
    GraphMat(W **_EdgeMat, E *_Elements, graph_size_t _VertexCount, graph_size_t _EdgeCount)
    {
        _vc = _VertexCount;
        _ec = _EdgeCount;
        _edgemat = new W*[_vc];
        for(graph_size_t i = 0; i < _vc; ++i)
            _edgemat[i] = new W[_vc];
        _elems = new E[_vc];
        _sels = new E[_vc];

        for (graph_size_t i = 0; i < _vc; ++i)
        {
            _elems[i] = _Elements[i];
            for (graph_size_t j = 0; j < _vc; ++j)
                _edgemat[i][j] = *((W*)_EdgeMat + i*_vc + j);
        }
    }
    GraphMat(GraphLnk<W, E>& _GraphLnk)
    {
        _vc = _GraphLnk._vc;
        _ec = _GraphLnk._ec;
        _edgemat = new W*[_vc];
        for(graph_size_t i = 0; i < _vc; ++i)
            _edgemat[i] = new W[_vc];
        _elems = new E[_vc];
        _sels = new E[_vc];

        VertexNode<W, E>* v = _GraphLnk._head;
        EdgeNode<W, E> * e = nullptr;

        for (graph_size_t i = 0; v != nullptr && i < _vc; ++i, v = v->_next)
        {
            _elems[i] = v->value();
            v->firstNeibor();
            e = v->_sel;
            if(e == nullptr)
                continue;
            for (graph_size_t j = 0; j < _vc; ++j)
            {
                if(i == j)
                    _edgemat[i][j] = 0;
                else if(j == e->out()->value())
                {
                    _edgemat[i][j] = e->weight();
                    if(v->nextNeibor() == nullptr)
                        continue;
                    e = v->_sel;
                }
                else
                    _edgemat[i][j] = INF;
            }
        }
    }
    ~GraphMat()
    {
        for(graph_size_t i = 0; i < _vc; ++i)
            delete [] _edgemat[i];
        delete [] _edgemat;
        delete [] _elems;
        delete [] _sels;
    }

    friend std::ostream &operator<<<>(std::ostream &_Ostream, GraphMat<W, E>& _GraphMat);
    friend class GraphLnk<W, E>;

    bool insertVertex(E _Vertex, E _Value);
    bool insertEdge(E _Vertex1, E _Vertex2, W _Weight);
    bool removeVertex(E _Vertex);
    bool removeEdge(E _Vertex1, E _Vertex2);
    bool empty(void) const;
    bool getWeight(E _Vertex1, E _Vertex2, W& _Dest) const;
    bool getFirstNeibor(E _Vertex, E& _Dest);
    bool getNextNeibor(E _Vertex, E& _Dest);

private:
    graph_size_t _vc = 0;
    graph_size_t _ec = 0;
    W **_edgemat = nullptr;
    E *_elems = nullptr;
    E * _sels = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename W, typename E>
std::ostream &operator<<(std::ostream &_Ostream, GraphMat<W, E>& _GraphMat)
{
    graph_size_t length = _GraphMat._vc;
    W **em = _GraphMat._edgemat;
    for (graph_size_t i = 0; i < length; ++i)
    {
        for (graph_size_t j = 0; j < length; ++j)
            _Ostream << ((j == 0) ? '\0' : ' ') << ((em[i][j] == INF) ? std::string("∞") : std::to_string(em[i][j]));
        _Ostream << std::endl;
    }
    return _Ostream;
}

template <typename W, typename E>
bool GraphMat<W, E>::insertVertex(E _Vertex, E _Value)
{
    if(_Vertex >= _vc)
        return false;
    _elems[_Vertex] = _Value;
    ++_vc;
    return true;
}


template <typename W, typename E>
bool GraphMat<W, E>::insertEdge(E _Vertex1, E _Vertex2, W _Weight)
{
    if(_Vertex1 >= _vc || _Vertex2 >= _vc)
        return false;
    _edgemat[_Vertex1][_Vertex2] = _Weight;
    ++_ec;
    return true;
}


template <typename W, typename E>
bool GraphMat<W, E>::removeVertex(E _Vertex)
{
    if(_Vertex >= _vc)
        return false;
    for(graph_size_t i = 0; i < _vc; ++i)
        _edgemat[_Vertex][i] = INF;
    _elems[_Vertex] = 0;
    --_vc;
    return true;
}


template <typename W, typename E>
bool GraphMat<W, E>::removeEdge(E _Vertex1, E _Vertex2)
{
    if(_Vertex1 >= _vc || _Vertex2 >= _vc)
        return false;
    _edgemat[_Vertex1][_Vertex2] = INF;
    --_ec;
    return true;
}


template <typename W, typename E>
bool GraphMat<W, E>::empty(void) const
{
    return (_vc == 0);
}


template <typename W, typename E>
bool GraphMat<W, E>::getWeight(E _Vertex1, E _Vertex2, W& _Dest) const
{
    if(_Vertex1 >= _vc || _Vertex2 >= _vc)
        return false;
    _Dest = _edgemat[_Vertex1][_Vertex2];
    return true;
}

template <typename W, typename E>
bool GraphMat<W, E>::getFirstNeibor(E _Vertex, E& _Dest)
{
    if(_Vertex >= _vc)
        return false;
    _sels[_Vertex] = 0;
    _Dest = _elems[_sels[_Vertex]];
    return true;
}


template <typename W, typename E>
bool GraphMat<W, E>::getNextNeibor(E _Vertex, E& _Dest)
{
    if(_Vertex >= _vc)
        return false;
    ++_sels[_Vertex];
    _Dest = _elems[_sels[_Vertex]];
    return true;
}

#endif