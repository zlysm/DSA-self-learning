//
// Created by zlysm on 10/25/22.
//

#ifndef DSA_GRAPH_H
#define DSA_GRAPH_H

using VStatus = enum {
    UNDISCOVERED, DISCOVERED, VISITED
};

using EType = enum {
    UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD
};  //边的类型

template<typename Tv, typename Te>
class Graph {
private:
    void reset() {
        for (Rank i = 0; i < n; ++i) {  //所有顶点的
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1; //状态，时间标签
            parent(i) = -1;
            priority(i) = INT_MAX; //（在遍历树中的）父节点，优先级数
            for (Rank j = 0; j < n; j++) //所有边的
                if (exists(i, j)) type(i, j) = UNDETERMINED; //类型
        }
    }

    void BFS(Rank, int &);  //广度优先

    void DFS(Rank, int &);  //深度优先

    void BCC(Rank, int &, Stack<Rank> &);  //基于DFS的双连通分量分解算法

    bool TSort(Rank, int &, Stack<Tv> *);  //基于DFS的拓扑排序算法

    template<typename PU>
    void PFS(Rank, PU); //优先级搜索框架

public:
// 顶点
    int n{}; //顶点总数

    virtual Rank insert(Tv const &) = 0;

    virtual Tv remove(Rank) = 0;  //删除顶点及其关联边，返回该顶点信息

    virtual Tv &vertex(Rank) = 0;  //顶点数据

    virtual int inDegree(Rank) = 0;

    virtual int outDegree(Rank) = 0;

    virtual Rank firstNbr(Rank) = 0;  //首个邻接顶点

    virtual Rank nextNbr(Rank, Rank) = 0;  //顶点（相对当前邻居的）下一邻居

    virtual VStatus &status(Rank) = 0;  //顶点状态

    virtual int &dTime(Rank) = 0;  //时间标签

    virtual int &fTime(Rank) = 0;  //时间标签

    virtual Rank &parent(Rank) = 0;

    virtual int &priority(Rank) = 0;

// 边：约定无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
    int e{};  //总边数

    virtual bool exists(Rank, Rank) = 0;  //边(u, v)是否存在

    virtual void insert(Te const &, int, Rank, Rank) = 0;  //两顶点间插入带权重的边

    virtual Te remove(Rank, Rank) = 0;

    virtual EType &type(Rank, Rank) = 0;  //边的类型

    virtual Te &edge(Rank, Rank) = 0;  //边的数据

    virtual int &weight(Rank, Rank) = 0;

// 算法
    void bfs(Rank);  //广度优先搜索算法

    void dfs(Rank);  //深度优先搜索算法

    void bcc(Rank);  //基于DFS的双连通分量分解算法

    Stack<Tv> *tSort(Rank);  //基于DFS的拓扑排序算法

    void prim(Rank);  //最小支撑树Prim算法

    void dijkstra(Rank);  //最短路径Dijkstra算法

    template<typename PU>
    void pfs(Rank, PU);  //优先级搜索框架
};

#include "Graph_bfs.h"

#endif //DSA_GRAPH_H
