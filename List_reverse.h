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
    for (int i = 1; i < _size; i += 2)   //�����ס�ĩ�ڵ㿪ʼ��������ڣ�׽�Եؽ����Գƽڵ��������
        std::swap((p = p->succ)->data, (q = q->pred)->data);
}

////version B
//template<typename T>
//void List<T>::reverse() {
//    if (_size < 2) return;
//    for (ListNodePosi<T> p = header; p; p = p->pred)
//        std::swap(p->pred, p->succ);  //��ǰ������ν������ڵ��ǰ�������ָ��
//    std::swap(header, trailer);
//}

////version C
//template<typename T>
//void List<T>::reverse() {
//    if (_size < 2) return; //ƽ�����
//    ListNodePosi<T> p;
//    ListNodePosi<T> q;
//    for (p = header, q = p->succ; p != trailer; p = q, q = p->succ)
//        p->pred = q; //��ǰ������εߵ����ڵ��ǰ��ָ��
//    trailer->pred = NULL; //��������β�ڵ��ǰ��ָ��
//    for (p = header, q = p->pred; p != trailer; p = q, q = p->pred)
//        q->succ = p; //��ǰ������εߵ����ڵ�ĺ��ָ��
//    header->succ = NULL; //��������ͷ�ڵ�ĺ��ָ��
//    swap(header, trailer); //ͷ��β�ڵ㻥��
//}

#endif //DSA_LIST_REVERSE_H
