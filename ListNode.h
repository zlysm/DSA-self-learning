//
// Created by zlysm on 9/1/22.
//

#ifndef DSA_LISTNODE_H
#define DSA_LISTNODE_H

typedef int Rank;
#define ListNodePosi(T) ListNode<T>

template<typename T>
struct ListNode {
    //成员
    T data;
    ListNodePosi(T) pred;
    ListNodePosi(T) succ;  //数值、前驱、后继
    //constructor
    ListNode() {};  //针对header和trailer癿极造

    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) : data(e), pred(p), succ(s) {}
    //操作接口
    ListNodePosi(T) insertAsPred(T const &e);  //紧靠弼前节点之前揑入新节点

    ListNodePosi(T) insertAsSucc(T const &e);
};

#endif //DSA_LISTNODE_H
