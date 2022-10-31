//
// Created by zlysm on 9/4/22.
//

#ifndef DSA_QUEUE_H
#define DSA_QUEUE_H

#include "List.h"

template<typename T>
class Queue : public List<T> {  //badminton bucket
public:
    void enqueue(T const &e) { this->insertAsLast(e); }  //入队：尾部揑入

    T dequeue() { return this->remove(this->first()); }  //出队：首部初除

    T &front() { return this->first()->data; }  //队首
};

#endif //DSA_QUEUE_H
