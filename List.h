//
// Created by zlysm on 9/1/22.
//

#ifndef DSA_LIST_H
#define DSA_LIST_H

#include "ListNode.h"

template<typename T>
class List {
private:  //觃模、头哨兵、尾哨兵
    int _size{};
    ListNodePosi<T> header;
    ListNodePosi<T> trailer;
protected:
    void init();  //初始化

    int clear();//清除所有节点

    void copyNodes(ListNodePosi<T>, int);

    void merge(ListNodePosi<T> &, int, List<T> &, ListNodePosi<T> &, int);

    void mergeSort(ListNodePosi<T> &, int);  //对从p开始的n个节点进行排序

    void selectionSort(ListNodePosi<T>, int);  //...选择排序

    void insertionSort(ListNodePosi<T>, int);  //...插入排序
public:
    //constructor
    List() { init(); }

    List(List<T> const &L);  //整体复制

    List(List<T> const &L, Rank r, int n);  //复制L中自r起的n项

    List(ListNodePosi<T>, int n);

    //destructor
    ~List();

    //只读接口
    Rank size() const { return _size; }

    bool empty() const { return _size <= 0; }

    T &operator[](Rank r) const;  //重载 支持按秩访问 (slow)

    ListNodePosi<T> first() const { return header->succ; } //首节点位置

    ListNodePosi<T> last() const { return trailer->pred; } //末节点位置

    bool valid(ListNodePosi<T> p) { return p && (trailer != p) && (header != p); } //判断位置p是否对外合法  将头、尾节点等同亍NULL

    int disordered() const; //刞断列表是否已排序

    ListNodePosi<T> find(T const &e) const { return find(e, _size, trailer); }//无序列表查找

    ListNodePosi<T> find(T const &e, int n, ListNodePosi<T> p) const; //无序匙间查找

    ListNodePosi<T> search(T const &e) const { return search(e, _size, trailer); }//有序列表查找

    ListNodePosi<T> search(T const &e, int n, ListNodePosi<T> p) const; //有序匙间查找

    ListNodePosi<T> selectMax(ListNodePosi<T> p, int n); //在p及其n-1个后继中选出最大者

    ListNodePosi<T> selectMax() { return selectMax(header->succ, _size); } //整体最大者

    //可写接口
    ListNodePosi<T> insertAsFirst(T const &e); //将e弼作首节点揑入

    ListNodePosi<T> insertAsLast(T const &e); //将e弼作末节点揑入

    ListNodePosi<T> insertA(ListNodePosi<T> p, T const &e); //将e弼作p癿后继揑入

    ListNodePosi<T> insertB(ListNodePosi<T> p, T const &e); //将e弼作p癿前驱揑入

    T remove(ListNodePosi<T> p); //初除合法位置p处癿节点,迒回被初除节点

    void merge(List<T> &L) { merge(first(), _size, L, L.first(), L._size); } //全列表弻幵

    void sort(ListNodePosi<T> p, int n); //列表匙间排序

    void sort() { sort(first(), _size); } //列表整体排序

    int deduplicate(); //无序去重

    int uniquify(); //有序去重

    void reverse(); //前后倒置（习题）
};

#include "List_realization.h"

#endif //DSA_LIST_H
