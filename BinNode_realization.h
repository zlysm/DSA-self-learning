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

template<typename T>
BinNodePosi<T> BinNode<T>::succ() { //定位节点v的直接后继
    BinNodePosi<T> s = this; //记录后继的临时变量
    if (rc) { //若有右孩子，则直接后继必在右子树中，具体地就是
        s = rc; //右子树中
        while (HasLChild(*s)) s = s->lc; //最靠左（最小）的节点
    } else { //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
        while (IsRChild(*s)) s = s->parent; //逆向地沿右向分支，不断朝左上方移动
        s = s->parent; //最后再朝右上方移动一步，即抵达直接后继（如果存在）
    }
    return s;
}

#endif //DSA_BINNODE_REALIZATION_H
