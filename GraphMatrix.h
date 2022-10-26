//
// Created by zlysm on 10/25/22.
//

#ifndef DSA_GRAPHMATRIX_H
#define DSA_GRAPHMATRIX_H

#include "Vector.h"
#include "Graph.h"

template<typename Tv>
struct Vertex {
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    int dTime, fTime;
    Rank parent;
    int priority;

    explicit Vertex(Tv const &d = (Tv) 0) :  //构造新顶点
            data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
            dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template<typename Te>
struct Edge {
    Te data;
    int weight;
    EType type;

    Edge(Te const &d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};

template<typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv>> V;  //顶点集（向量）

    Vector<Vector<Edge<Te> *>> E;  //边集（邻接矩阵）

public:
    GraphMatrix() { Graph<Tv, Te>::n = Graph<Tv, Te>::e = 0; }

    ~GraphMatrix() {
        for (Rank j = 0; j < Graph<Tv, Te>::n; ++j)
            for (Rank k = 0; k < Graph<Tv, Te>::e; ++k)
                delete E[j][k];
    }

// 顶点的基本操作：查询第i个顶点（0 <= i < n）
    virtual Tv &vertex(Rank i) { return V[i].data; }

    virtual int inDegree(Rank i) { return V[i].inDegree; }

    virtual int outDegree(Rank i) { return V[i].outDegree; }

    virtual Rank firstNbr(Rank i) { return nextNbr(i, Graph<Tv, Te>::n); }

    virtual Rank nextNbr(Rank i, Rank j) {
        while ((-1 < j) && (!exists(i, --j)));  //逆向线性试探
        return j;
    }

    virtual VStatus &status(Rank i) { return V[i].status; }

    virtual int &dTime(Rank i) { return V[i].dTime; }

    virtual int &fTime(Rank i) { return V[i].fTime; }

    virtual Rank &parent(Rank i) { return V[i].parent; }

    virtual int &priority(Rank i) { return V[i].priority; }

// 顶点的动态操作
    virtual Rank insert(Tv const &vertex) {
        for (Rank j = 0; j < Graph<Tv, Te>::n; ++j) E[j].insert(NULL);  //各顶点预留一条潜在的关联边
        ++Graph<Tv, Te>::n;
        E.insert(Vector<Edge<Te> *>(Graph<Tv, Te>::n, Graph<Tv, Te>::n, (Edge<Te> *) NULL));  //创建新顶点对应的边向量
        return V.insert(Vertex<Tv>(vertex));  //顶点向量增加一个顶点
    }

    virtual Tv remove(Rank i) {  //删除第i个顶点及其关联边（0 <= i < n）
        for (Rank j = 0; j < Graph<Tv, Te>::n; j++)  //所有出边
            if (exists(i, j)) {  //逐条删除
                delete E[i][j];
                V[j].inDegree--;
                Graph<Tv, Te>::e--;
            }
        E.remove(i);  //删除第i行
        Graph<Tv, Te>::n--;
        Tv vBak = vertex(i);
        V.remove(i);  //删除顶点i
        for (Rank j = 0; j < Graph<Tv, Te>::n; j++)  //所有入边
            if (Edge<Te> *x = E[j].remove(i)) { //逐条删除
                delete x;
                V[j].outDegree--;
                Graph<Tv, Te>::e--;
            }
        return vBak; //返回被删除顶点的信息
    }

// 边的确认操作
    virtual bool exists(Rank i, Rank j) //边(i, j)是否存在
    { return (i < Graph<Tv, Te>::n) && (j < Graph<Tv, Te>::n) && E[i][j] != NULL; }  //i, j 小于总顶点n且矩阵不为空

// 边的基本操作：查询顶点i与j之间的联边（0 <= i, j < n且exists(i, j)）
    virtual EType &type(Rank i, Rank j) { return E[i][j]->type; }

    virtual Te &edge(Rank i, Rank j) { return E[i][j]->data; }

    virtual int &weight(Rank i, Rank j) { return E[i][j]->weight; }

// 边的动态操作
    virtual void insert(Te const &edge, int w, Rank i, Rank j) { //插入权重为w的边(i, j)
        if (exists(i, j)) return;  //确保该边尚不存在
        E[i][j] = new Edge<Te>(edge, w);  //创建新边
        Graph<Tv, Te>::e++;
        V[i].outDegree++;
        V[j].inDegree++;  //更新边计数与关联顶点的度数
    }

    virtual Te remove(Rank i, Rank j) {  //删除顶点i和j之间的联边（exists(i, j)）
        Te eBak = edge(i, j);
        delete E[i][j];
        E[i][j] = NULL;  //备份后删除边记录
        Graph<Tv, Te>::e--;
        V[i].outDegree--;
        V[j].inDegree--;  //更新边计数与关联顶点的度数
        return eBak;  //返回被删除边的信息
    }
};

#endif //DSA_GRAPHMATRIX_H
