#include <iostream>
#include "CirQueue.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
const int MaxSize = 10;
using elem_t = int;
bool comp(elem_t a, elem_t b)
{
    return a < b;
}
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    CirQueue<elem_t> * cq = new CirQueue<elem_t>(MaxSize);
    elem_t e;
    while(cin >> e)
        cq->push(e);

    cout << cq << endl;
    cq->sort(comp);
    cout << cq << endl;
    delete cq;
    return 0;
}