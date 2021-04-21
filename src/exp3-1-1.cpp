#include <iostream>
#include <string>
#include "SeqStack.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
typedef int elem_t;
typedef SeqStack<elem_t> Stack;
const array_size_t MAX_SIZE = 50;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    Stack * S = new Stack(MAX_SIZE);
    for(int i = 1; i != 7; ++i)
        S->push(i);

    cout << S->GetTop() << endl;
    cout << S->length() << endl;
    delete S;
    return 0;
}