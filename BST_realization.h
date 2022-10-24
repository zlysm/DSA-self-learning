//
// Created by zlysm on 10/23/22.
//

#ifndef DSA_BST_REALIZATION_H
#define DSA_BST_REALIZATION_H

/******************************************************************************************
 * 按照“3 + 4”结构联接3个节点及其四棵子树，返回重组之后的局部子树根节点位置（即b）
 * 子树根节点与上层节点之间的双向联接，均须由上层调用者完成
 * 可用于AVL和RedBlack的局部平衡调整
 ******************************************************************************************/
template<typename T>
BinNodePosi<T> BST<T>::connect34(
        BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c,
        BinNodePosi<T> T0, BinNodePosi<T> T1, BinNodePosi<T> T2, BinNodePosi<T> T3
) {
    //*DSA*/print(a); print(b); print(c); printf("\n");
    a->lc = T0;
    if (T0) T0->parent = a;
    a->rc = T1;
    if (T1) T1->parent = a;
    updateHeight(a);
    c->lc = T2;
    if (T2) T2->parent = c;
    c->rc = T3;
    if (T3) T3->parent = c;
    updateHeight(c);
    b->lc = a;
    a->parent = b;
    b->rc = c;
    c->parent = b;
    updateHeight(b);
    return b; //该子树新的根节点
}

template<typename T>
BinNodePosi<T> &BST<T>::search(const T &e) { //在BST中查找关键码e
    if (!BinTree<T>::_root || e == BinTree<T>::_root->data) {
        _hot = NULL;
        return BinTree<T>::_root;
    } //空树，或恰在树根命中
    for (_hot = BinTree<T>::_root;;) { //否则，自顶而下
        BinNodePosi<T> &v = (e < _hot->data) ? _hot->lc : _hot->rc; //确定方向，深入一层
        if (!v || e == v->data) return v;
        _hot = v; //一旦命中或抵达叶子，随即返回
    } //返回目标节点位置的引用，以便后续插入、删除操作
} //无论命中或失败，_hot均指向v之父亲（v是根时，hot为NULL）

template<typename T>
BinNodePosi<T> BST<T>::insert(const T &e) {
    BinNodePosi<T> &x = search(e);
    if (x) return x;  //已有雷同节点
    x = new BinNode<T>(e, _hot);
    ++BinTree<T>::_size;
    BinTree<T>::updateHeightAbove(x);
    return x;
}

template<typename T>
static BinNodePosi<T> removeAt(BinNodePosi<T> &x, BinNodePosi<T> &hot) {
    BinNodePosi<T> w = x;
    BinNodePosi<T> succ = NULL;
    if (!HasLChild (*x))   //若*x的左子树为空，则可直接将*x替换为其右子树，左子树同理
        succ = x = x->rc;
    else if (!HasRChild (*x))
        succ = x = x->lc;
    else { //若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要
        w = w->succ(); //（在右子树中）找到*x的直接后继*w
        std::swap(x->data, w->data); //交换*x和*w的数据元素
        BinNodePosi<T> u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc; //隔离节点*w   ?????
    }
    hot = w->parent; //记录实际被删除节点的父亲
    if (succ) succ->parent = hot; //并将被删除节点的接替者与hot相联
    release(w->data);
    release(w);
    return succ; //释放被摘除节点，返回接替者
}

template<typename T>
bool BST<T>::remove(const T &e) {
    BinNodePosi<T> &x = search(e);
    if (!x) return false;
    removeAt(x, _hot);
    BinTree<T>::_size--;
    BinTree<T>::updateHeightAbove(_hot);
    return true;
}


#endif //DSA_BST_REALIZATION_H
