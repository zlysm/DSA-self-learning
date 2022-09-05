//
// Created by zlysm on 9/5/22.
//

#ifndef DSA_BINTREE_REALIZATION_H
#define DSA_BINTREE_REALIZATION_H

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi<T> x) //更新节点x高度
{ return x->height = 1 + std::max(stature(x->lc), stature(x->rc)); }

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi<T> x) {  //更新高度
    while (x) {
        updateHeight(x);
        x = x->parent;  //从x出发，覆盖历代祖先。可优化
    }
}

template<typename T>
BinNodePosi<T> BinTree<T>::insert(const T &e) {
    _size = 1;
    return _root = new BinNode<T>(e);  //将e当作根节点插入空的二叉树
}

template<typename T>
BinNodePosi<T> BinTree<T>::insert(const T &e, BinNodePosi<T> x) {  //e插入为x的左孩子
    _size++;
    x.insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template<typename T>
BinNodePosi<T> BinTree<T>::insert(BinNodePosi<T> x, const T &e) {  //e插入为x的右孩子
    _size++;
    x.insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

#endif //DSA_BINTREE_REALIZATION_H
