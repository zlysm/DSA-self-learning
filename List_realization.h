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

#endif //DSA_LIST_REALIZATION_H
