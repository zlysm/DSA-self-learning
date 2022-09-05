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
template<typename VST>
void BinNode<T>::travIn(VST &visit) { //二叉树中序遍历算法统一入口
    switch (rand() % 5) { //此处暂随机选择以做测试，共五种选择
        case 1:
            travIn_I1(this, visit);
            break; //迭代版#1
        case 2:
            travIn_I2(this, visit);
            break; //迭代版#2
        case 3:
            travIn_I3(this, visit);
            break; //迭代版#3
        case 4:
            travIn_I4(this, visit);
            break; //迭代版#4
        default:
            travIn_R(this, visit);
            break; //逑弻版
    }
}

#endif //DSA_BINNODE_REALIZATION_H
