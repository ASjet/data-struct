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
    cout << " (2)依次插入a,b,c,d,e元素" << endl;
    A->insert(0, 'a');
    A->insert(1, 'b');
    A->insert(2, 'c');
    A->insert(3, 'd');
    A->insert(4, 'e');
    cout << " (3)输出单链表L:";
    cout << A << endl;
    cout << " (4)单链表L长度:" << A->length() << endl;
    cout << " (5)单链表L为" << ((A->empty()) ? "空" : "非空") << endl;
    cout << " (6)单链表L的第3个元素:" << A->getElem(2) << endl;
    cout << " (7)元素a的位置:" << A->find('a') + 1 << endl;
    cout << " (8)在第4个元素位置上插入f元素" << endl;
    A->insert(3, 'f');
    cout << " (9)输出单链表L:" << A << endl;
    cout << " (10)删除L的第3个元素" << endl;
    A->remove(2);
    cout << " (11)输出单链表L:" << A << endl;
    cout << " (12)释放单链表L" << endl;

    // Addon
    cout << "附加题:" << endl << A << endl;

    LinerLink<elem_t> *B = new LinerLink<elem_t>;
    Node<elem_t> *head, *tail, *p, *next;
    Node<elem_t> *A_head, *A_tail;
    Node<elem_t> *B_head, *B_tail;
    link_size_t A_len = 0, B_len = 0, len = A->length();

    head = A->head();
    tail = A->tail();
    p = head;

    for (link_size_t i = 0; i != len; ++i)
    {
        next = p->next();
        if (p->value() % 2 == 0)
        {
            A->insert(0, p->value());
            A_head = A->head();
            if(A_len == 0)
                A_tail = A->head();
            ++A_len;
        }
        else
        {
            A->push(p->value());
            B_tail = A->tail();
            if(B_len == 0)
                B_head = A->tail();
            ++B_len;
        }
        delete p;
        p = next;
    }

    A->initialize(A_head, A_tail, A_len);
    B->initialize(B_head, B_tail, B_len);
    cout << A << endl << B << endl;
    delete A;
    delete B;
    return 0;
}