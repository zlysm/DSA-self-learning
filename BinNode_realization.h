//
// Created by zlysm on 9/5/22.
//

#ifndef DSA_BINNODE_REALIZATION_H
#define DSA_BINNODE_REALIZATION_H

template<typename T>
BinNodePosi<T> BinNode<T>::insertAsLC(const T &e) {  //将e作为弼前节点癿左孩子揑入二叉树
    return lc = new BinNode(e, this);
}

template<typename T>
BinNodePosi<T> BinNode<T>::insertAsRC(const T &e) {
    return rc = new BinNode(e, this);
}

template<typename T>
int BinNode<T>::size() { //统计当前节点后代总数，即以其为根的子树规模
    int s = 1; //计入本身
    if (lc) s += lc->size(); //递归计入左子树规模
    if (rc) s += rc->size(); //递归计入右子树规模
    return s;
}

#endif //DSA_BINNODE_REALIZATION_H
