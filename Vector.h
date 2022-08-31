//
// Created by zlysm on 8/16/22.
//

#ifndef DSA_VECTOR_H
#define DSA_VECTOR_H

typedef int Rank;
#define DEFAULT_CAPACITY 3

template<typename T>
class Vector {
protected:
    Rank _size{};
    int _capacity{};
    T *_elem;

    void copyFrom(T const *A, Rank lo, Rank hi);

    void expand();

    void shrink();

    bool bubble(Rank lo, Rank hi);

    void bubbleSort(Rank lo, Rank hi);

    Rank max(Rank lo, Rank hi);

    void selectionSort(Rank lo, Rank hi);

    void merge(Rank lo, Rank mi, Rank hi);

    void mergeSort(Rank lo, Rank hi);

    Rank partition(Rank lo, Rank hi);

    void quickSort(Rank lo, Rank hi);

    void heapSort(Rank lo, Rank hi);

public:
    //constructor
    explicit Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {  //容量为c、觃模为s、所有元素刜始为v
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }  //s<=c

    Vector(T const *A, Rank n) { copyFrom(A, 0, n); }  //数组整体复刢

    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }  //区间

    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); } //向量整体复刢

    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //区间
    //destructor
    ~Vector() { delete[] _elem; }

    //只读接口
    Rank size() const { return _size; }

    bool empty() const { return !_size; }

    int disordered() const;

    Rank find(T const &e) const { return find(e, 0, _size); } //无序向量整体查找

    Rank find(T const &e, Rank lo, Rank hi) const; //无序向量匙间查找

    Rank search(T const &e) const { //有序向量整体查找
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }

    Rank search(T const &e, Rank lo, Rank hi) const; //有序向量区间查找

    //可写访问接口
    T &operator[](Rank r) const; //重载下标操作符，可以类似亍数组形式引用各元素

    Vector<T> &operator=(Vector<T> const &); //重载赋值操作符，以便直接克隆向量

    T remove(Rank r);

    int remove(Rank lo, Rank hi); //初除秩在匙间[lo, hi)之内的元素

    Rank insert(Rank r, T const &e);  //揑入元素

    Rank insert(T const &e) { return insert(_size, e); } //默讣作为末元素揑入

    void sort(Rank lo, Rank hi); //对[lo, hi)排序

    void sort() { sort(0, _size); } //整体排序

    void unsort(Rank lo, Rank hi); //对[lo, hi)置乱

    void unsort() { unsort(0, _size); } //整体置乱

    int deduplicate(); //无序去重

    int uniquify(); //有序去重

    // 遍历
    void traverse(void (* )(T &)); //遍历（使用函数指针，叧读戒尿部性修改）

    template<typename VST>
    void traverse(VST &); //遍历（使用函数对象，可全尿性修改）
};

#include "Vec.h"


#endif //DSA_VECTOR_H
