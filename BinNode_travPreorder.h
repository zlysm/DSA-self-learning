//
// Created by zlysm on 9/6/22.
//

#ifndef DSA_BINNODE_TRAVPREORDER_H
#define DSA_BINNODE_TRAVPREORDER_H

template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST &visit) {
    switch (rand() % 3) {
        case 1:
            travPre_I1(this, visit);
            break;
        case 2:
            travPre_I2(this, visit);
            break;
        default:
            travPre_R(this, visit);
            break;
    }
}

template<typename T, typename VST>
void travPre_R(BinNodePosi<T> x, VST &visit) {  //二叉树先序遍历算法（递归版）
    if (!x) return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template<typename T, typename VST>
void travPre_I1(BinNodePosi<T> x, VST &visit) {
    Stack<BinNodePosi<T>> S;  //辅助栈
    if (x) S.push(x);  //根节点入栈
    while (!S.empty()) {
        x = S.pop();
        visit(x->data);  //弹出并访问当前节点，其非空孩子的入栈次序为先右后左
        if (HasRChild(*x)) S.push(x->rc);
        if (HasLChild(*x)) S.push(x->lc);
    }
}

template<typename T, typename VST>
void travPre_I2(BinNodePosi<T> x, VST &visit) {
    Stack<BinNodePosi<T>> S;
    while (true) {
        visitAlongVine(x, visit, S);  //从当前节点出发，逐批访问
        if (S.empty()) break;
        x = S.pop();  //直到栈空弹出下一批的起点
    }
}

template<typename T, typename VST>
static void visitAlongVine(BinNodePosi<T> x, VST &visit, Stack<BinNodePosi<T>> &S) {
    while (x) {  //从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
        visit(x->data);
        S.push(x->rc);  //右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
        x = x->lc;  //沿左分支深入一层
    }
}

#endif //DSA_BINNODE_TRAVPREORDER_H
