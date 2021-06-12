#include <iostream>

#include "GraphMat.h"
#include "GraphLnk.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using weight_t = int;
using elem_t = int;
const graph_size_t MAXV = 6;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    weight_t A[MAXV][MAXV] = {
        {0, 5, INF, 7, INF, INF},
        {INF, 0, 4, INF, INF, INF},
        {8, INF, 0, INF, INF, 9},
        {INF, INF, 5, 0, INF, 6},
        {INF, INF, INF, 5, 0, INF},
        {3, INF, INF, INF, 1, 0}
    };
    graph_size_t ec = 10;
    graph_size_t vc = MAXV;
    elem_t E[MAXV] = {0, 1, 2, 3, 4, 5};

    GraphMat<weight_t, elem_t> * gm1 = new GraphMat<weight_t, elem_t>((weight_t**)A, E, vc, ec);
    GraphLnk<weight_t, elem_t> * gl1 = new GraphLnk<weight_t, elem_t>((weight_t**)A, E, vc, ec);
    GraphMat<weight_t, elem_t> gm2(*gl1);
    GraphLnk<weight_t, elem_t> gl2(*gm1);
    cout << *gm1 << endl;
    cout << gm2 << endl;
    cout << *gl1 << endl;
    cout << gl2 << endl;
    delete gl1;
    delete gm1;
    return 0;
}
