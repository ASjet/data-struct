#include <iostream>
#include <string>
#include <vector>
#include "LinerLink.h"
#include "Sqlist.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void testSqlist(void);
////////////////////////////////////////////////////////////////////////////////
int main(void)
{ // 0 0 2 4 4 4 7 7
     Sqlist<int> * L = new Sqlist<int>(50);
     L->insert(0, 0);
     L->insert(1, 0);
     L->insert(2, 2);
     L->insert(3, 4);
     L->insert(4, 4);
     L->insert(5, 4);
     L->insert(6, 7);
     L->insert(7, 7);
     L->disp();
     L->unique();
     L->disp();
     delete L;

    return 0;
}

void testSqlist(void)
{

}