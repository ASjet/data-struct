#include <iostream>
#include "BinTree.h"
#include <string>
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
using elem_t = char;
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    BinTree<elem_t> * bt = new BinTree<elem_t>;
    // LinerLink * lnk = new LinerLink<elem_t>;
    LinerLink<elem_t> lnk;
    string po, io;
    cout << "先序遍历:";
    cin >> po;
    cout << "中序遍历:";
    cin >> io;
    bt->initialize(po.c_str(), io.c_str(), po.length());
    bt->postOrder(&lnk);
    cout << &lnk << endl;
    return 0;
}
