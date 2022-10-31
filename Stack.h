//
// Created by zlysm on 9/2/22.
//

#ifndef DSA_STACK_H
#define DSA_STACK_H

#include "Vector.h"

template<typename T>
class Stack : public Vector<T> {
public:
    void push(T const &e) { this->insert(e); }

    T pop() { return this->remove(this->size() - 1); }

    T &top() { return (*this)[this->size() - 1]; }
};

#endif //DSA_STACK_H
