//
// Created by zlysm on 10/23/22.
//

#ifndef DSA_BST_H
#define DSA_BST_H

#include "BinTree.h"

template<typename T>
class BST : public BinTree<T> {
protected:
    BinNodePosi<T> _hot;

    BinNodePosi<T> connect34( //按照“3 + 4”结构，联接3个节点及四棵子树
            BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>,
            BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>);

    BinNodePosi<T> rotateAt(BinNodePosi<T> x); //对x及其父亲、祖父做统一旋转调整
public:
    virtual BinNodePosi<T> &search(const T &e);

    virtual BinNodePosi<T> insert(const T &e);

    virtual bool remove(const T &e);
};

#endif //DSA_BST_H
