//
// Created by zlysm on 9/5/22.
//

#ifndef DSA_BINNODE_MACRO_H
#define DSA_BINNODE_MACRO_H

//Basic
/******************************************************************************************
 * BinNode状态与性质的判断
 ******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )

/******************************************************************************************
 * 与BinNode具有特定关系的节点及指针
 ******************************************************************************************/
#define sibling(p) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc ) /*兄弟*/
#define uncle(x) ( sibling( (x)->parent ) ) /*叔叔*/
#define FromParentTo(x) ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) ) /*来自父亲的引用*/

//AVL
#define HeightUpdated(x) ( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )/*高度更新常规条件*/
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //理想平衡条件
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //平衡因子
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVL平衡条件

//RedBlack
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) ) //外部节点也视作黑节点
#define IsRed(p) ( ! IsBlack(p) ) //非黑即红
#define BlackHeightUpdated(x) (( stature((x).lc) == stature((x).rc)) && \
   ((x).height == ( IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1 )))  /*RedBlack高度更新条件*/

#endif //DSA_BINNODE_MACRO_H
