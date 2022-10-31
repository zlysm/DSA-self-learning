//
// Created by zlysm on 10/31/22.
//

#ifndef DSA_AVL_H
#define DSA_AVL_H

#include "BST.h"

template<typename T>
class AVL : public BST<T> {
public:
    BinNodePosi<T> insert(const T &e);

    bool remove(const T &e);
};

#include "AVL_marco.h"

#endif //DSA_AVL_H
