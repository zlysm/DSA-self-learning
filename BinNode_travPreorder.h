//
// Created by zlysm on 2022/9/6.
//

#ifndef DSA_BINNODE_TRAVPREORDER_H
#define DSA_BINNODE_TRAVPREORDER_H

template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST &visit) { //二叉树先序遍历算法统一入口
    switch (rand() % 3) { //此处暂随机选择以做测试，共三种选择
        case 1:
            travPre_I1(this, visit);
            break; //迭代版#1
        case 2:
            travPre_I2(this, visit);
            break; //迭代版#2
        default:
            travPre_R(this, visit);
            break; //递归版
    }
}

#endif //DSA_BINNODE_TRAVPREORDER_H
