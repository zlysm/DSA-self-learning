//
// Created by zlysm on 8/31/22.
//

#ifndef DSA_VECTOR_PARTITION_H
#define DSA_VECTOR_PARTITION_H

//LGU version
template<typename T>
//轴点构造算法：通过调整元素位置构造区间[lo, hi)的轴点，并返回其秩
Rank Vector<T>::partition(Rank lo, Rank hi) { //LGU版
    std::swap(_elem[lo], _elem[lo + rand() % (hi - lo)]); //任选一个元素与首元素交换
    T pivot = _elem[lo]; //以首元素为候选轴点——经以上交换，等效于随机选取
    int mi = lo;
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //   ---- L < [lo] ----- ] ----- [lo] <= G --- ] [ ----- Unknown -------
    // X x . . . . . . . . . x . . . . . . . . . . . x . . . . . . . . . . x X
    // |                     |                       |                       |
    // lo (pivot candidate)  mi                      k                       hi
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    for (Rank k = lo + 1; k < hi; k++) //自左向右扫描
        if (_elem[k] < pivot) //若当前元素_elem[k]小于pivot，则
            std::swap(_elem[++mi], _elem[k]); //将_elem[k]交换至原mi之后，使L子序列向右扩展
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //   --------- L < [lo] ---------- ] ------------- [lo] <= G ----------]
    // X x . . . . . . . . . . . . . . x . . . . . . . . . . . . . . . . . x X
    // |                               |                                     |
    // lo (pivot candidate)            mi                                    hi
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    std::swap(_elem[lo], _elem[mi]); //候选轴点归位
    return mi; //返回轴点的秩
}

////DUP version
//template<typename T>
////轴点构造算法：通过调整元素位置构造区间[lo, hi)的轴点，并返回其秩
//Rank Vector<T>::partition(Rank lo, Rank hi) { //DUP版：可优化处理多个关键码雷同的退化情况
//    std::swap(_elem[lo], _elem[lo + rand() % (hi - lo)]); //任选一个元素与首元素交换
//    hi--;
//    T pivot = _elem[lo]; //以首元素为候选轴点——经以上交换，等效于随机选取
//    while (lo < hi) { //从向量的两端交替地向中间扫描
//        while (lo < hi)
//            if (pivot < _elem[hi]) //在大于pivot的前提下
//                hi--; //向左拓展右端子向量
//            else //直至遇到不大于pivot者
//            {
//                _elem[lo++] = _elem[hi];
//                break;
//            } //将其归入左端子向量
//        while (lo < hi)
//            if (_elem[lo] < pivot) //在小于pivot的前提下
//                lo++; //向右拓展左端子向量
//            else //直至遇到不小于pivot者
//            {
//                _elem[hi--] = _elem[lo];
//                break;
//            } //将其归入右端子向量
//    } //assert: lo == hi
//    _elem[lo] = pivot; //将备份的轴点记录置于前、后子向量之间
//    return lo; //返回轴点的秩
//}

////DUP1 version
//template<typename T>
////轴点构造算法：通过调整元素位置构造区间[lo, hi)的轴点，并返回其秩
//Rank Vector<T>::partition(Rank lo, Rank hi) { //DUP1版：与DUP版等价，类似于与LUG版等价的LUG1版
//    std::swap(_elem[lo], _elem[lo + rand() % (hi - lo)]); //任选一个元素与首元素交换
//    hi--;
//    T pivot = _elem[lo]; //以首元素为候选轴点——经以上交换，等效于随机选取
//    while (lo < hi) { //从向量的两端交替地向中间扫描
//        while ((lo < hi) && (pivot < _elem[hi])) //在大于pivot的前提下
//            hi--; //向左拓展右端子向量
//        if (lo < hi) _elem[lo++] = _elem[hi]; //不大于pivot者归入左端子向量
//        while ((lo < hi) && (_elem[lo] < pivot)) //在小于pivot的前提下
//            lo++; //向右拓展左端子向量
//        if (lo < hi) _elem[hi--] = _elem[lo]; //不小于pivot者归入右端子向量
//    } //assert: lo == hi
//    _elem[lo] = pivot; //将备份的轴点记录置于前、后子向量之间
//    return lo; //返回轴点的秩
//}

////LUG version
//template<typename T>
////轴点构造算法：通过调整元素位置构造区间[lo, hi)的轴点，并返回其秩
//Rank Vector<T>::partition(Rank lo, Rank hi) { //LUG版本：基本形式
//    std::swap(_elem[lo], _elem[lo + rand() % (hi - lo)]); //任选一个元素与首元素交换
//    hi--;
//    T pivot = _elem[lo]; //以首元素为候选轴点——经以上交换，等效于随机选取
//    while (lo < hi) { //从向量的两端交替地向中间扫描
//        while ((lo < hi) && (pivot <= _elem[hi])) //在不小于pivot的前提下
//            hi--; //向左拓展右端子向量
//        _elem[lo] = _elem[hi]; //小于pivot者归入左侧子序列
//        while ((lo < hi) && (_elem[lo] <= pivot)) //在不大于pivot的前提下
//            lo++; //向右拓展左端子向量
//        _elem[hi] = _elem[lo]; //大于pivot者归入右侧子序列
//    } //assert: lo == hi
//    _elem[lo] = pivot; //将备份的轴点记录置于前、后子向量之间
//    return lo; //返回轴点的秩
//}

////LUG1 version
//template<typename T>
////轴点构造算法：通过调整元素位置构造区间[lo, hi)的轴点，并返回其秩
//Rank Vector<T>::partition(Rank lo, Rank hi) { //LUG1版：与LUG版等价，类似于与DUP版等价的DUP1版
//    std::swap(_elem[lo], _elem[lo + rand() % (hi - lo)]); //任选一个元素与首元素交换
//    hi--;
//    T pivot = _elem[lo]; //以首元素为候选轴点——经以上交换，等效于随机选取
//    while (lo < hi) { //从向量的两端交替地向中间扫描
//        while ((lo < hi) && (pivot <= _elem[hi])) //在不小于pivot的前提下
//            hi--; //向左拓展右端子向量
//        if (lo < hi) _elem[lo++] = _elem[hi]; //小于pivot者归入左侧子向量
//        while ((lo < hi) && (_elem[lo] <= pivot)) //在保证不大于pivot的前提下
//            lo++; //向右拓展左端子向量
//        if (lo < hi) _elem[hi--] = _elem[lo]; //大于pivot者归入右侧子向量
//    } //assert: lo == hi
//    _elem[lo] = pivot; //将备份的轴点记录置于前、后子向量之间
//    return lo; //返回轴点的秩
//}

#endif //DSA_VECTOR_PARTITION_H
