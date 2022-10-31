//
// Created by zlysm on 10/31/22.
//

#ifndef DSA_AVL_REALIZATION_H
#define DSA_AVL_REALIZATION_H

template<typename T>
BinNodePosi<T> AVL<T>::insert(const T &e) {
    BinNodePosi<T> &x = search(e);
    if (x) return x;  //确认目标节点不存在
    BinNodePosi<T> xx = x = new BinNode<T>(e, AVL<T>::_hot);
    ++AVL<T>::_size;  // 此时，x的父亲_hot若增高，则其祖父有可能失衡
    for (BinNodePosi<T> g = AVL<T>::_hot; g; g = g->parent)  //从x之父出发向上，逐层检查各代祖先g
        if (!AvlBalanced(*g)) {  //can't use "FromParentTo" marco due to template class
            IsRoot(*g) ? this->_root : (IsLChild(*g) ? (*g).parent->lc : (*g).parent->rc)
                                               = rotateAt(tallerChild(tallerChild(g)));
            break;  //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将子树重新接入原树
        } else  //未失衡只需更新其高度（注意：即便g未失衡，高度亦可能增加）
            updateHeight(g);
    return xx;  //返回新节点位置
}//无论e是否存在于原树中，总有AVL::insert(e)->data == e

#endif //DSA_AVL_REALIZATION_H
