#include <iostream>
#include <string>
#include <vector>
#include "Sqlist.h"
#define MAX_SIZE 50
typedef char elem_t;
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    Sqlist<elem_t> * L = new Sqlist<elem_t>;
    cout << "顺序表的基本运算如下:" << endl
         << " (1)初始化顺序表L" << endl;
    L->initialize(MAX_SIZE);
    cout << " (2)依次插入a,b,c,d,e元素" << endl;
    L->insert(0, 'a');
    L->insert(1, 'b');
    L->insert(2, 'c');
    L->insert(3, 'd');
    L->insert(4, 'e');
    cout << " (3)输出顺序表L:";
    L->disp();
    cout << " (4)顺序表L长度:" << L->length() << endl;
    cout << " (5)顺序表L为" << ((L->empty())? "空" : "非空") << endl;
    cout << " (6)顺序表L的第3个元素:" << L->getElem(2) << endl;
    cout << " (7)元素a的位置:" << L->find('a') + 1 << endl;
    cout << " (8)在第4个元素位置上插入f元素" << endl;
    L->insert(3, 'f');
    cout << " (9)输出顺序表L:";
    L->disp();
    cout << " (10)删除L的第3个元素" << endl;
    L->remove(2);
    cout << " (11)输出顺序表L:";
    L->disp();
    cout << " (12)释放顺序表L" << endl;
    delete L;

    return 0;
}