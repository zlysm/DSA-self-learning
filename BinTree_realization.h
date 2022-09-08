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
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template<typename T>
BinNodePosi<T> BinTree<T>::insert(BinNodePosi<T> x, const T &e) {  //e插入为x的右孩子
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template<typename T>
BinNodePosi<T> BinTree<T>::attach(BinTree<T> *&S, BinNodePosi<T> x) {  //将S当作节点x的左子树接入二叉树，S本身置空
    if (x->lc = S->_root) x->lc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x;   //释放原树，返回接入位置
}

template<typename T>
BinNodePosi<T> BinTree<T>::attach(BinNodePosi<T> x, BinTree<T> *&S) { //x->rc == NULL 将S当作节点x的右子树接入二叉树，S本身置空
    if (x->rc = S->_root) x->rc->parent = x; //接入
    _size += S->_size;
    updateHeightAbove(x); //更新全树规模与x所有祖先的高度
    S->_root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x; //释放原树，返回接入位置
}

template<typename T>
int BinTree<T>::remove(BinNodePosi<T> x) {  //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
    FromParentTo(*x) = NULL;  //切断来自父节点的指针
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;  //删除子树x，更新规模，返回删除节点总数
}

template<typename T>
static int removeAt(BinNodePosi<T> x) {
    if (!x) return 0;  //递归基：空树
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);  //递归释放左、右子树
    release(x->data);
    release(x);
    return n;
}

template<typename T>
BinTree<T> *BinTree<T>::secede(BinNodePosi<T> x) {
    FromParentTo(*x) = NULL;  //切断来自父节点的指针
    updateHeightAbove(x->parent);
    auto *S = new BinTree<T>;
    S->_root = x;
    x->parent = NULL;  //新树以x为根
    S->_size = x->size();
    _size -= S->_size;
    return S;  //更新规模，返回分离出来的子树
}

#endif //DSA_BINTREE_REALIZATION_H
