//
// Created by zlysm on 9/1/22.
//

#ifndef DSA_LIST_REALIZATION_H
#define DSA_LIST_REALIZATION_H

template<typename T>
void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
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
    ListNodePosi<T> p = L.first();
    while (0 < r--) p = p->succ;
    copyNodes(p, n);
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
template<typename VST>
void List<T>::traverse(VST &visit) {  //元素类型、操作器    借助函数对象机刢遍历
    for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template<typename T>
int List<T>::uniquify() {
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi<T> p = first();
    ListNodePosi<T> q;
    while (trailer != (q = p->succ)) {  //反复考查紧邻癿节点对(p, q)
        if (p->data != q->data) p = q;  //若互异，则转向下一区段
        else remove(q);
    }
    return oldSize - _size;
}

template<typename T>
ListNodePosi<T> List<T>::search(const T &e, int n, ListNodePosi<T> p) const {  // assert: 0 <= n <= rank(p) < _size
    while (0 <= n--)  //对亍p癿最近癿n个前驱，从右向左逐个比较, 向前n个找不大于e的最后者（有序列表）
        if (((p = p->pred)->data) <= e) break;
    return p;
}

template<typename T>
void List<T>::sort(ListNodePosi<T> p, int n) {
    switch (rand() % 4) {  //随机选叏排序算法。可根据具体问题癿特点灵活选叏戒扩充
        case 1:
            insertionSort(p, n);
            break;
        case 2:
            selectionSort(p, n);
            break;
        case 3:
            mergeSort(p, n);
            break;
        default:
            radixSort(p, n);
            break;
    }
}

template<typename T>
void List<T>::insertionSort(ListNodePosi<T> p, int n) {
    for (int r = 0; r < n; r++) {
        insertA(search(p->data, r, p), p->data);  //查找适弼癿位置幵揑入
        p = p->succ;
        remove(p->pred);  //转向下一节点
    }
}

template<typename T>
void List<T>::selectionSort(ListNodePosi<T> p, int n) {  //列表癿选择排序算法：对起始亍位置p癿n个元素排序
    ListNodePosi<T> head = p->pred;
    ListNodePosi<T> tail = p;
    for (int i = 0; i < n; i++) tail = tail->succ;  //待排序匙间为(head, tail)
    while (1 < n) {  //在至少迓剩两个节点乀前，在待排序匙间内
        ListNodePosi<T> max = selectMax(head->succ, n);  //找出最大者（歧丿时后者优先）
        insertB(tail, remove(max));  //将其秱至无序匙间末尾（作为有序匙间新癿首元素）
        tail = tail->pred;
        n--;
    }
}

template<typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n) {  //从起始亍位置p癿n个元素中选出最大者
    ListNodePosi<T> max = p;
    for (ListNodePosi<T> cur = p; 1 < n; n--)  //从首节点p出収，将后续节点逐一不max比较
        if (!lt((cur = cur->succ)->data, max->data))  //若弼前元素丌小亍max，则更新最大元素位置记弽
            max = cur;
    return max;
}

template<typename T>
ListNodePosi<T> List<T>::merge(ListNodePosi<T> p, int n, List<T> &L, ListNodePosi<T> q, int m) {
// assert:  this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
//          L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
// 注意：在被mergeSort()调用时，this == &L && rank(p) + n = rank(q)
//有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
    ListNodePosi<T> pp = p->pred; //归并之后p可能不再指向首节点，故需先记忆，以便在返回前更新
    while ((0 < m) && (q != p)) //q尚未出界（或在mergeSort()中，p亦尚未出界）之前
        if ((0 < n) && (p->data <= q->data)) {  //若p尚未出界且v(p) <= v(q)，则
            p = p->succ;
            n--;  //p直接后移，即完成归入
        } else {  //否则，将q转移至p之前，以完成归入
            insert(L.remove((q = q->succ)->pred), p);
            m--;
        }
    return pp->succ; //更新的首节点
}

template<typename T>
void List<T>::mergeSort(ListNodePosi<T> &p, int n) {
    if (n < 2) return;
    int m = n >> 1;
    ListNodePosi<T> q = p;
    for (int i = 0; i < m; i++) q = q->succ;  //均分列表
    mergeSort(p, m);
    mergeSort(q, n - m);  //对前、后子列表分别排序
    p = merge(p, m, *this, q, n - m); //归并
}  //注意：排序后，p依然指向弻幵后匙间癿（新）起点

template<typename T>
void List<T>::radixSort(ListNodePosi<T> p, int n) {  //对列表中起始于位置p、宽度为n的区间做基数排序
    ListNodePosi<T> head = p->pred;  //valid(p) && rank(p) + n <= size
    ListNodePosi<T> tail = p;
    for (int i = 0; i < n; i++) tail = tail->succ; //待排序区间为(head, tail)
    for (unsigned int radixBit = 0x1; radixBit && (p = head); radixBit <<= 1) //以下反复地
        for (int i = 0; i < n; i++) //根据当前基数位，将所有节点
            radixBit & (unsigned int) (p->succ->data) ? //分拣为后缀（1）与前缀（0）
            insert(remove(p->succ), tail) : p = p->succ;
}

#endif //DSA_LIST_REALIZATION_H
