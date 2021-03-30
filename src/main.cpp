#include <iostream>
#include <string>
#include <vector>
#include "LinerLink.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    // LinerLink<int> link;
    auto link = new LinerLink<int>;
    link->push(5);
    link->push(1234);
    cout << link->length() << endl
         << link->pop() << endl
         << link->length() << endl
         << link->empty() << endl
         << link->pop() << endl
         << link->empty() << endl
         << link->length() << endl;
    link->insert(5,0);
    cout << link->getElement(0) << endl;
    link->remove(0);
    link->push(123);
    link->insert(10,1);
    cout << link->head() << endl
         << link->tail() << endl
         << link->pop() << endl
         << link->head() << endl
         << link->tail() << endl;
    delete link;
    return 0;
}