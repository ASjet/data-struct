#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include "BinNode.h"
#include "LinerLink.h"
#include "LinkQueue.h"
#include "LinkStack.h"

typedef int btree_size_t;

template <typename T>
class BinTree
{
public:
    BinTree()
    {
        _root = new BinNode<T>;
    }
    ~BinTree()
    {
        clear();
    }

    void clear(void);
    bool initialize(T *_Seq, btree_size_t _Length);
    bool initialize(T *_PreOrder, T *_InOrder, btree_size_t _Length);

    btree_size_t height(void) const;
    btree_size_t size(void) const;
    bool empty(void) const;
    BinNode<T> *root(void) const;

    void preOrder(LinerLink<T> *_Output) const;
    void inOrder(LinerLink<T> *_Output) const;
    void postOrder(LinerLink<T> *_Output) const;
    void levelOrder(LinerLink<T> *_Output) const;

    bool insert(T _Element);
    bool remove(T _Element);
    bool Find(const T _Element) const;

private:
    void preOrder(LinerLink<T> *_Output, BinNode<T> *_Root) const;
    void inOrder(LinerLink<T> *_Output, BinNode<T> *_Root) const;
    void postOrder(LinerLink<T> *_Output, BinNode<T> *_Root) const;
    void levelOrder(LinerLink<T> *_Output, BinNode<T> *_Root) const;

    bool initialize(T *_PreOrder, T *_InOrder, btree_size_t _Length, BinNode<T> *_Root);
    btree_size_t _size = 0;
    BinNode<T> *_root = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void BinTree<T>::clear(void)
{
    delete _root;
    _size = 0;
    _root = nullptr;
}


template <typename T>
bool BinTree<T>::initialize(T *_Seq, btree_size_t _Length)
{
    if(_Seq == nullptr || _Length < 1)
        return false;

    if (_root != nullptr)
        clear();

    _root = new BinNode<T>(_Seq[0]);
    if (_root == nullptr)
        return false;

    _size = 1;

    if (_Length == 1)
        return true;
    else
    {
        T tmp;
        BinNode<T> *p;
        for (btree_size_t i = 1; i < _Length; ++i)
        {
            p = _root;
            while (true)
            {
                if (_Seq[i] > p->value())
                {
                    if (p->_rnode != nullptr)
                        p = p->_rnode;
                    else
                    {
                        p->_rnode = new BinNode<T>(p, _Seq[i]);
                        if (p->_rnode == nullptr)
                        {
                            clear();
                            return false;
                        }
                        ++_size;
                        break;
                    }
                }
                else
                {
                    if (p->_lnode != nullptr)
                        p = p->_lnode;
                    else
                    {
                        p->_lnode = new BinNode<T>(p, _Seq[i]);
                        if (p->_lnode == nullptr)
                        {
                            clear();
                            return false;
                        }
                        ++_size;
                        break;
                    }
                }
            }
        }
    }
    return true;
}


template <typename T>
bool BinTree<T>::initialize(T *_PreOrder, T *_InOrder, btree_size_t _Length)
{
    if(_PreOrder == nullptr || _InOrder == nullptr || _Length < 1)
        return false;

    if (_root != nullptr)
        clear();

    _root = new BinNode<T>;
    if (_root == nullptr)
        return false;
    else
        return initialize(_PreOrder, _InOrder, _Length, _root);
}


template <typename T>
bool BinTree<T>::initialize(T *_PreOrder, T *_InOrder, btree_size_t _Length, BinNode<T> *_Root)
{
    // std::cout << _PreOrder[0] << '<' << std::endl;
    _Root->value() = _PreOrder[0];
    ++_size;
    if (_Length == 1)
        return true;

    btree_size_t pos = 0;
    for (int i = 0; i < _Length; ++i)
        if (_InOrder[i] == _PreOrder[0])
        {
            pos = i;
            break;
        }

    if (pos == 0)
    {
        _Root->_rnode = new BinNode<T>(_root);
        if (_Root->_rnode == nullptr)
        {
            clear();
            return false;
        }
        else
            return initialize(_PreOrder + 1, _InOrder + 1, _Length - 1, _Root->_rnode);
    }
    else if ((pos + 1) == _Length)
    {
        _Root->_lnode = new BinNode<T>(_Root);
        if (_Root->_lnode == nullptr)
        {
            clear();
            return false;
        }
        else
            return initialize(_PreOrder + 1, _InOrder, _Length - 1, _Root->_lnode);
    }
    else
    {
        _Root->_lnode = new BinNode<T>(_Root);
        _Root->_rnode = new BinNode<T>(_Root);
        if (_Root->_lnode == nullptr || _Root->_rnode == nullptr)
        {
            clear();
            return false;
        }
        else
        {
            bool flag1 = initialize(_PreOrder + 1, _InOrder, pos, _Root->_lnode);
            bool flag2 = initialize(_PreOrder + pos + 1, _InOrder + pos + 1, _Length - pos - 1, _Root->_rnode);
            return flag1 && flag2;
        }
    }
}


template <typename T>
btree_size_t BinTree<T>::height(void) const
{
    LinkStack<BinNode<T> *> *lnk = new LinkStack<BinNode<T> *>;
    if(lnk == nullptr)
        return -1;
    btree_size_t height = 1;
    BinNode<T> *p = nullptr;
    if (_root->_lnode == nullptr && _root->_rnode == nullptr)
        return (height > _size) ? _size : height;
    else
    {
        p = _root;
        if (_root->_rnode != nullptr)
            lnk->push(_root->_rnode);
        if (_root->_lnode != nullptr)
            p = _root->_lnode;
        height = (lnk->length() > height) ? lnk->length() : height;
    }
    delete lnk;
}



template <typename T>
btree_size_t BinTree<T>::size(void) const
{
    return _size;
}


template <typename T>
bool BinTree<T>::empty(void) const
{
    return (_size == 0);
}


template <typename T>
BinNode<T> *BinTree<T>::root(void) const
{
    return _root;
}


template <typename T>
void BinTree<T>::preOrder(LinerLink<T> *_Output) const
{
    preOrder(_Output, _root);
}


template <typename T>
void BinTree<T>::preOrder(LinerLink<T> *_Output, BinNode<T> *_Root) const
{
    if (_Root != nullptr)
    {
        _Output->insert(-1, _Root->value());
        preOrder(_Output, _Root->_lnode);
        preOrder(_Output, _Root->_rnode);
    }
}


template <typename T>
void BinTree<T>::inOrder(LinerLink<T> *_Output) const
{
    inOrder(_Output, _root);
}


template <typename T>
void BinTree<T>::inOrder(LinerLink<T> *_Output, BinNode<T> *_Root) const
{
    if (_Root != nullptr)
    {
        inOrder(_Output, _Root->_lnode);
        _Output->insert(-1, _Root->value());
        inOrder(_Output, _Root->_rnode);
    }
}


template <typename T>
void BinTree<T>::postOrder(LinerLink<T> *_Output) const
{
    postOrder(_Output, _root);
}


template <typename T>
void BinTree<T>::postOrder(LinerLink<T> *_Output, BinNode<T> *_Root) const
{
    if (_Root != nullptr)
    {
        postOrder(_Output, _Root->_lnode);
        postOrder(_Output, _Root->_rnode);
        _Output->insert(-1, _Root->value());
    }
}


template <typename T>
void BinTree<T>::levelOrder(LinerLink<T> *_Output) const
{
    levelOrder(_Output, _root);
}


template <typename T>
void BinTree<T>::levelOrder(LinerLink<T> *_Output, BinNode<T> *_Root) const
{
    LinkQueue<BinNode<T> *> *q = new LinkQueue<BinNode<T> *>;
    if(q == nullptr)
        return;
    BinNode<T> *tmp, *left, *right;
    if (_Root != nullptr)
    {
        q->push(_Root);
        while (!q->empty())
        {
            if(q->pop(tmp))
            {
                left = tmp->_lnode;
                right = tmp->_rnode;
            }
            _Output->insert(-1, tmp->value());

            if (left != nullptr)
                q->push(left);

            if (right != nullptr)
                q->push(right);
        }
    }
    delete q;
}


#endif