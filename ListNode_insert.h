//
// Created by zlysm on 9/1/22.
//

#ifndef DSA_LISTNODE_INSERT_H
#define DSA_LISTNODE_INSERT_H

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(const T &e) {  //将e紧靠弼前节点乀前揑入亍弼前节点所属列表（讴有哨兵头节点header）
    auto x = new ListNode(e, pred, this);  //创建新节点  位于当前节点和前一个节点之间
    pred->succ = x;  //前个节点的后继为x
    pred = x;  //将本节点的前驱改为x
    return x;
}

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(const T &e) {
    auto x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

#endif //DSA_LISTNODE_INSERT_H
