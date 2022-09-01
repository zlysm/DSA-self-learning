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

#endif //DSA_LIST_REALIZATION_H
