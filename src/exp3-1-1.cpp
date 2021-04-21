#include <iostream>
#include <string>
#include "SeqStack.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
typedef int elem_t;
const array_size_t MAX_SIZE = 50;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    SeqStack<elem_t> * S = new SeqStack<elem_t>(MAX_SIZE);
    for(int i = 1; i != 7; ++i)
        S->push(i);

    cout << S->GetTop() << endl;
    cout << S->length() << endl;
    delete S;
    return 0;
}