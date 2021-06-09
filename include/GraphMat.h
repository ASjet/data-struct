#ifndef GRAPHMAT_H
#define GRAPHMAT_H

#include <iostream>
#include <string>
#include "Graph.h"
#define INF -1

template <typename W, typename E>
class GraphMat;

template <typename W, typename E>
std::ostream &operator<<(std::ostream &_Ostream, GraphMat<W, E> _GraphMat);

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
        for (graph_size_t i = 0; i < _vc; ++i)
        {
            _elems[i] = _Elements[i];
            for (graph_size_t j = 0; j < _vc; ++j)
                _edgemat[i][j] = *((W*)_EdgeMat + i*_vc + j);
        }
    }
    ~GraphMat()
    {
        // for(graph_size_t i = 0; i < _vc; ++i)
        //     delete [] _edgemat[i];
        // delete [] _edgemat;
        // delete [] _elems;
    }

    friend std::ostream &operator<<<>(std::ostream &_Ostream, GraphMat<W, E> _GraphMat);

private:
    graph_size_t _vc = 0;
    graph_size_t _ec = 0;
    W **_edgemat = nullptr;
    E *_elems = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename W, typename E>
std::ostream &operator<<(std::ostream &_Ostream, GraphMat<W, E> _GraphMat)
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

#endif