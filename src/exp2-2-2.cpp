#include <iostream>
#include <string>
#include "LinerLink.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    LinerLink<int> * LF = new LinerLink<int>;
    LinerLink<int> * LR = new LinerLink<int>;
    LF->insert(0,123);
    LR->insert(LR->length(),456);
    LF->disp();
    LR->disp();
    delete LF;
    delete LR;
    return 0;
}