//
// Created by zlysm on 9/2/22.
//

#ifndef DSA_STACK_H
#define DSA_STACK_H

#include "Vector.h"

template<typename T>
class Stack : public Vector<T> {
public:
    void push(T const &e) { Vector<T>::insert(e); }

    T pop() { return Vector<T>::remove(Vector<T>::size() - 1); }

    T &top() { return (*this)[Vector<T>::size() - 1]; }
};

#endif //DSA_STACK_H
