//
// Created by zlysm on 9/4/22.
//

#ifndef DSA_QUEUE_H
#define DSA_QUEUE_H

#include "List.h"

template<typename T>
class Queue : public List<T> {  //badminton bucket
public:
    void enqueue(T const &e) { List<T>::insertAsLast(e); }  //入队：尾部揑入

    T dequeue() { return List<T>::remove(List<T>::first()); }  //出队：首部初除

    T &front() { return List<T>::first()->data; }  //队首
};

#endif //DSA_QUEUE_H
