//
// Created by zlysm on 9/6/22.
//

#ifndef DSA_BINNODE_TRAVINORDER_H
#define DSA_BINNODE_TRAVINORDER_H

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
            break; //递归版
    }
}

template<typename T, typename VST>
void travIn_R(BinNodePosi<T> x, VST &visit) { //二叉树中序遍历算法（递归版）
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template<typename T>
static void goAlongVine(BinNodePosi<T> x, Stack<BinNodePosi<T>> &S) {  //从当前节点出发，沿左分支不断深入，直至没有左分支的节点
    while (x) {
        S.push(x);
        x = x->lc;
    } //当前节点入栈后随即向左侧分支深入，迭代直到无左孩子
}

template<typename T, typename VST>
void travIn_I1(BinNodePosi<T> x, VST &visit) {
    Stack<BinNodePosi<T>> S;
    while (true) {
        goAlongVine(x, S); //从当前节点出发，逐批入栈
        if (S.empty()) break; //直至所有节点处理完毕
        x = S.pop();
        visit(x->data); //弹出栈顶节点并访问之
        x = x->rc; //转向右子树
    }
}

template<typename T, typename VST>
void travIn_I2(BinNodePosi<T> x, VST &visit) { //二叉树中序遍历算法（迭代版#2）
    Stack<BinNodePosi<T>> S; //辅助栈
    while (true)
        if (x) {
            S.push(x); //根节点进栈
            x = x->lc; //深入遍历左子树
        } else if (!S.empty()) {
            x = S.pop(); //尚未访问的最低祖先节点退栈
            visit(x->data); //访问该祖先节点
            x = x->rc; //遍历祖先的右子树
        } else
            break; //遍历完成
}

template<typename T, typename VST>
void travIn_I3(BinNodePosi<T> x, VST &visit) { //二叉树中序遍历算法（迭代版#3，无需辅助栈）
    bool backtrack = false; //前一步是否刚从左子树回溯——省去栈，仅O(1)辅助空间
    while (true)
        if (!backtrack && HasLChild (*x)) //若有左子树且不是刚刚回溯，则
            x = x->lc; //深入遍历左子树
        else { //否则——无左子树或刚刚回溯（相当于无左子树）
            visit(x->data); //访问该节点
            if (HasRChild (*x)) { //若其右子树非空，则
                x = x->rc; //深入右子树继续遍历
                backtrack = false; //并关闭回溯标志
            } else { //若右子树空，则
                if (!(x = x->succ())) break; //回溯（含抵达末节点时的退出返回）
                backtrack = true; //并设置回溯标志
            }
        }
}

template<typename T, typename VST>
void travIn_I4(BinNodePosi<T> x, VST &visit) { //二叉树中序遍历（迭代版#4，无需栈或标志位）
    while (true)
        if (HasLChild (*x)) //若有左子树，则
            x = x->lc; //深入遍历左子树
        else { //否则
            visit(x->data); //访问当前节点，并
            while (!HasRChild (*x)) //不断地在无右分支处
                if (!(x = x->succ())) return; //回溯至直接后继（在没有后继的末节点处，直接退出）
                else visit(x->data); //访问新的当前节点
            x = x->rc; //（直至有右分支处）转向非空的右子树
        }
}

#endif //DSA_BINNODE_TRAVINORDER_H
