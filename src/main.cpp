#include <iostream>
#include <string>
#include <vector>
#include "Link.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    Link<int> link;
    link.push(5);
    link.push(1234);
    cout << link.length() << endl
         << link.pop() << endl
         << link.length() << endl
         << link.empty() << endl
         << link.pop() << endl
         << link.empty() << endl
         << link.length() << endl;
    link.insert(5,0);
    cout << link.getElement(0) << endl;
    link.remove(0);
    link.insert(10,1);
    cout << link.head() << endl
         << link.tail() << endl
         << link.pop() << endl
         << link.head() << endl
         << link.tail() << endl;
    return 0;
}