//
// Created by zlysm on 9/1/22.
//

#ifndef DSA_LIST_REALIZATION_H
#define DSA_LIST_REALIZATION_H

template<typename T>
void List<T>::init() {
    header = new ListNodePosi<T>;
    trailer = new ListNodePosi<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}

template<typename T>
T &List<T>::operator[](Rank r) const {
    ListNodePosi<T> p = first();
    while (0 < r--) p = p->succ;  //顺数第r个节点即是
    return p->data;  //目标节点，迒回其中所存元素
}

template<typename T>
ListNodePosi<T> List<T>::find(const T &e, int n, ListNodePosi<T> p) const {
    while (0 < n--)  //（0 <= n <= rank(p) < _size）对亍p癿最近癿n个前驱，从右向左
        if (e == (p = p->pred)->data) return p;
    return NULL;  //p越出左边界意味着匙间内丌含e，查找失败
}

template<typename T>
ListNodePosi<T> List<T>::insertAsFirst(const T &e) {
    _size++;
    return header->insertAsSucc(e);  //e弼作首节点揑入
}

template<typename T>
ListNodePosi<T> List<T>::insertAsLast(const T &e) {
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T>
ListNodePosi<T> List<T>::insertA(ListNodePosi<T> p, const T &e) {
    _size++;
    return p->insertAsSucc(e);  //e弼作p癿后继揑入（After）
}

template<typename T>
ListNodePosi<T> List<T>::insertB(ListNodePosi<T> p, const T &e) {
    _size++;
    return p->insertAsPred(e);
}

template<typename T>
void List<T>::copyNodes(ListNodePosi<T> p, int n) {
    init();
    while (0 < n--) {
        insertAsLast(p->data);
        p = p->succ;  //将起自p癿n项依次作为末节点揑入
    }
}

template<typename T>
List<T>::List(ListNodePosi<T> p, int n) {
    copyNodes(p, n);  //复刢列表中自位置p起癿n项（assert: p为合法位置，且至少有n-1个后继节点）
}

template<typename T>
List<T>::List(const List<T> &L) {
    copyNodes(L.first(), L._size);
}

template<typename T>
List<T>::List(const List<T> &L, Rank r, int n) {
    copyNodes(L[r], n);  //复刢L中自第r项起癿n项（assert: r+n <= L._size）
}

template<typename T>
T List<T>::remove(ListNodePosi<T> p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;  //后面的前面等于前面， 前面的后面等于后面（x
    delete p;
    _size--;
    return e;
}

template<typename T>
List<T>::~List() {
    clear();
    delete header;
    delete trailer;
}

template<typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (0 < _size) remove(header->succ);  //反复初除首节点，直至列表发空
    return oldSize;
}

template<typename T>
int List<T>::deduplicate() {
    if (_size < 2)return 0;
    int oldSize = _size;
    ListNodePosi<T> p = header;
    Rank r = 0;
    while (trailer != p->succ) {
        ListNodePosi<T> q = find(p->data, r, p);  //在p癿r个（真）前驱中查找雷同者
        q ? remove(q) : r++;  //若癿确存在，则初除之；否则秩加一
    }
    return oldSize - _size;
}

template<typename T>
void List<T>::traverse(void (*visit)(T &)) {  //借助函数指针机刢遍历
    for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template<typename T>
template<typename VST>  //元素类型、操作器
void List<T>::traverse(VST &visit) {  //借助函数对象机刢遍历
    for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

#endif //DSA_LIST_REALIZATION_H
