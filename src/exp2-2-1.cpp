#include <iostream>
#include <string>
#include "LinerLink.h"
#define MAX_SIZE 50
typedef char elem_t;
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    LinerLink<elem_t> *A = new LinerLink<elem_t>;
    cout << "单链表的基本运算如下:" << endl
         << " (1)初始化单链表L" << endl;
    // L->initialize(MAX_SIZE);
    cout << " (2)依次插入a,b,c,d,e元素" << endl;
    A->insert(0, 'a');
    A->insert(1, 'b');
    A->insert(2, 'c');
    A->insert(3, 'd');
    A->insert(4, 'e');
    cout << " (3)输出单链表L:";
    A->disp();
    cout << " (4)单链表L长度:" << A->length() << endl;
    cout << " (5)单链表L为" << ((A->empty()) ? "空" : "非空") << endl;
    cout << " (6)单链表L的第3个元素:" << A->getElem(2) << endl;
    cout << " (7)元素a的位置:" << A->find('a') + 1 << endl;
    cout << " (8)在第4个元素位置上插入f元素" << endl;
    A->insert(3, 'f');
    cout << " (9)输出单链表L:";
    A->disp();
    cout << " (10)删除L的第3个元素" << endl;
    A->remove(2);
    cout << " (11)输出单链表L:";
    A->disp();
    cout << " (12)释放单链表L" << endl;
    // addon
    LinerLink<int> *B = new LinerLink<int>;
    Node<int> *head, *tail;
    Node<int> *A_head, *A_tail;
    Node<int> *B_head, *B_tail;
    int A_len = 0, B_len = 0;
    for (int i = 0; i != 10; ++i)
        A->push(i);
    A->disp();
    head = A->head();
    tail = A->tail();
    for (Node<int> *p = A->head(), *next; p != tail; /*void*/)
    {
        next = p->next();
        if (p->value() % 2 == 0)
        {
            A->insert(0, p->value());
            A_head = A->head();
            if(A_len == 0)
                A_tail = A->head();
            ++A_len;
            delete p;
        }
        else
        {
            A->insert(A->length(), p->value());
            B_tail = A->tail();
            if(B_len == 0)
                B_head = A->tail();
            ++B_len;
            delete p;
        }
        p = next;
    }
    A->initialize(A_head, A_tail, A_len);
    B->initialize(B_head, B_tail, B_len);
    A->disp();
    B->disp();
    delete A;
    delete B;
    return 0;
}