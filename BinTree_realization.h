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

#endif //DSA_BINTREE_REALIZATION_H
