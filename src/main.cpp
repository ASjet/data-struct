#include <iostream>
#include <cstdio>
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
void Addon2(void);
////////////////////////////////////////////////////////////////////////////////
int main(void)
{ // 0 0 2 4 4 4 7 7
    Sqlist<int> *L = new Sqlist<int>(50);
    L->insert(0, 0);
    L->insert(1, 0);
    L->insert(2, 2);
    L->insert(3, 4);
    L->insert(4, 4);
    L->insert(5, 4);
    L->insert(6, 7);
    L->insert(7, 7);
    cout << L << endl;
    L->unique();
    cout << L << endl;
    Addon2();
    delete L;

    return 0;
}

void Addon2(void)
{
    int var1, i;
    char var2[5];
    printf("var1 变量的地址： %p\n", &var1);
    for (i = 0; i < 2; i++)
        printf("char型var2[%d] 变量的地址： %p\n", i, &var2[i]);
}