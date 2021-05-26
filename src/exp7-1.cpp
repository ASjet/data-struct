#include <iostream>
#include <string>
#include <vector>
#include "BinTree.h"
#include "LinerLink.h"
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using elem_t = char;
string str("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    cout << "二叉树的基本运算如下:" << endl;
    cout << "\t(1)创建二叉树" << endl;
    BinTree<elem_t> * bt = new BinTree<elem_t>;
    BinNode<elem_t> * p;
    bt->initializeTable(str);
    cout << "\t(2)输出二叉树:" << bt << endl;
    p = bt->find('H');
    cout << "\t(3)H节点:左孩子为" << p->lnode()->value()
         << " 右孩子为" << p->rnode()->value() << endl;
    cout << "\t(4)二叉树b的高度:" << bt->height() << endl;
    cout << "\t(5)释放二叉树" << endl;
    delete bt;
    return 0;
}