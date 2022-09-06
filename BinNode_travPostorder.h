//
// Created by zlysm on 9/6/22.
//

#ifndef DSA_BINNODE_TRAVPOSTORDER_H
#define DSA_BINNODE_TRAVPOSTORDER_H

template<typename T>
template<typename VST>
void BinNode<T>::travPost(VST &visit) { //二叉树后序遍历算法统一入口
    switch (rand() % 2) { //此处暂随机选择以做测试，共两种选择
        case 1:
            travPost_I(this, visit);
            break; //迭代版
        default:
            travPost_R(this, visit);
            break; //递归版
    }
}

template<typename T, typename VST>
void travPost_R(BinNodePosi<T> x, VST &visit) {
    if (!x) return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template<typename T, typename VST>
void travPost_I(BinNodePosi<T> x, VST &visit) {
    Stack<BinNodePosi<T>> S;
    if (x) S.push(x);  //根节点入栈
    while (!S.empty()) {  //x始终为当前节点
        if (S.top() != x->parent)  //若栈顶非x之父（而为右兄）
            gotoLeftmostLeaf(S);  //则在其右兄子树中找到HLVFL（相当于递归深入）
        x = S.pop();
        visit(x->data);  //弹出栈顶（即前一节点之后继），并访问之
    }
}

template<typename T>
static void gotoLeftmostLeaf(Stack<BinNodePosi<T>> &S) {  //在以S栈顶节点为根的子树中，找到最高左侧可见叶节点，沿途所遇节点依次入栈
    while (BinNodePosi<T> x = S.top()) //自顶而下，反复检查当前节点（即栈顶）
        if (HasLChild (*x)) { //尽可能向左
            if (HasRChild (*x)) S.push(x->rc); //若有右孩子，优先入栈
            S.push(x->lc); //然后才转至左孩子
        } else //实不得已
            S.push(x->rc); //才向右
    S.pop(); //返回之前，弹出栈顶的空节点
}

#endif //DSA_BINNODE_TRAVPOSTORDER_H
