#include <iostream>
#include <string>
#include <vector>
#include "CLink.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
typedef char elem_t;
template<typename T>
Node<T>* SearchLocate(CLink<T> * _CLink, clink_size_t _Index);
template<typename T>
void addon2(clink_size_t _N, clink_size_t _X, clink_size_t _Y);
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    elem_t arr[] = "abcde";
    CLink<elem_t> * CL_L = new CLink<elem_t>;
    CLink<elem_t> * CL_R = new CLink<elem_t>;
    CL_L->initializeL(arr,5);
    CL_R->initializeR(arr,5);
    CL_L->disp(0);
    CL_R->disp(0);
    delete CL_L;
    delete CL_R;

    // 附加题
    cout << "附加题" << endl;
    int n = 15;
    int x = 10;
    int y = 18;
    Node<int> * p = nullptr;
    CLink<int> * CL = new CLink<int>;
    for(int i = 0; i < n; ++i)
        CL->insert(CL->length(), i);

    CL->disp(0);
    p = SearchLocate(CL, x);
    if(p != nullptr)
        cout << p->value() << endl;

    p = SearchLocate(CL, y);
    if(p != nullptr)
        cout << p->value() << endl;

    delete CL;


    return 0;
}

template<typename T>
Node<T>* SearchLocate(CLink<T> * _CLink, clink_size_t _Index)
{
    Node<T> * head = _CLink->head();
    Node<T> * p = head, *res = head;
    if(_CLink->length() < _Index)
    {
        std::cerr << "Index out of range" << std::endl;
        return nullptr;
    }
    for(clink_size_t i = 0; i < _Index-1; ++i)
        p = p->next();
    while(p->next() != head)
    {
        p = p->next();
        res = res->next();
    }
    return res;
}

template<typename T>
void addon2(clink_size_t _N, clink_size_t _X, clink_size_t _Y)
{
    CLink<int> * CL = new CLink<int>;
    for(int i = 0; i < _N; ++i)
        CL->insert(CL->length(), i);

    Node<T> * p = CL->head();
    while(p != nullptr)
    {
        for(clink_size_t i = 0; i < _X; ++i)
            p = p->next();
        cout << p->value() << ' ';
        p = p->next();

        delete p->prev();
        for(clink_size_t i = 0; i < _Y; ++i)
            p = p->prev();
        cout << p->value() << ' ';
        p = p->prev();
        delete p->next();
    }
    cout << endl;
}