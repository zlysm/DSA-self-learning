//
// Created by zlysm on 2022/9/2.
//

#ifndef DSA_LIST_REVERSE_H
#define DSA_LIST_REVERSE_H

//version A
template<typename T>
void List<T>::reverse() {
    ListNodePosi<T> p = header;
    ListNodePosi<T> q = trailer;
    for (int i = 1; i < _size; i += 2)   //（从首、末节点开始）由外而内，捉对地交换对称节点的数据项
        std::swap((p = p->succ)->data, (q = q->pred)->data);
}

////version B
//template<typename T>
//void List<T>::reverse() {
//    if (_size < 2) return;
//    for (ListNodePosi<T> p = header; p; p = p->pred)
//        std::swap(p->pred, p->succ);  //自前向后，依次交换各节点的前驱、后继指针
//    std::swap(header, trailer);
//}

////version C
//template<typename T>
//void List<T>::reverse() {
//    if (_size < 2) return; //平凡情况
//    ListNodePosi<T> p;
//    ListNodePosi<T> q;
//    for (p = header, q = p->succ; p != trailer; p = q, q = p->succ)
//        p->pred = q; //自前向后，依次颠倒各节点的前驱指针
//    trailer->pred = NULL; //单独设置尾节点的前驱指针
//    for (p = header, q = p->pred; p != trailer; p = q, q = p->pred)
//        q->succ = p; //自前向后，依次颠倒各节点的后继指针
//    header->succ = NULL; //单独设置头节点的后继指针
//    swap(header, trailer); //头、尾节点互换
//}

#endif //DSA_LIST_REVERSE_H
