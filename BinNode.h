//
// Created by zlysm on 9/5/22.
//

#ifndef DSA_BINNODE_H
#define DSA_BINNODE_H

#define stature(p) ((p) ? (p)->height : -1)  //节点高度

typedef enum {  //节点颜色
    RB_RED, RB_BLACK
} RBColor;

template<typename T>
struct BinNode;

template<typename T> using BinNodePosi = BinNode<T>;

template<typename T>
struct BinNode {
    //member
    T data;

    BinNodePosi<T> parent;

    BinNodePosi<T> lc;

    BinNodePosi<T> rc;  //父节点及左、右孩子

    int height;

    int npl;  //Null Path Length（左式堆，也可直接用height代替）

    RBColor color;  //颜色（红黑树）

    //constructor
    BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}

    explicit BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL,
            int h = 0, int l = 1, RBColor c = RB_RED) :
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

    //interface
    int size();

    BinNodePosi<T> insertAsLC(T const &);

    BinNodePosi<T> insertAsRC(T const &);

    BinNodePosi<T> succ();  //取当前节点的直接后继

    template<typename VST>
    void travLevel(VST &); //子树层次遍历

    template<typename VST>
    void travPre(VST &); //子树先序遍历

    template<typename VST>
    void travIn(VST &); //子树中序遍历

    template<typename VST>
    void travPost(VST &); //子树后序遍历

    template<typename VST>
    void traverse(VST &); //自定义遍历

    // 比较器、判等器（各列其一，其余自行补充）
    bool operator<(BinNode const &bn) { return data < bn.data; } //小于

    bool operator==(BinNode const &bn) { return data == bn.data; } //等于

    BinNodePosi<T> zig(); //顺时针旋转

    BinNodePosi<T> zag(); //逆时针旋转

    BinNodePosi<T> balance(); //完全平衡化

    BinNodePosi<T> imitate(const BinNodePosi<T>); //临摹
};

#include "BinNode_realization.h"
#include "BinNode_macro.h"  //快捷方式

#endif //DSA_BINNODE_H
