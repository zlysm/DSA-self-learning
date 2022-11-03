//
// Created by zlysm on 11/3/22.
//

#ifndef DSA_GRAPH_REALIZATION_H
#define DSA_GRAPH_REALIZATION_H

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(Rank s) {
    reset();
    int clock = 0;
    Rank v = s;
    do  //一旦遇到尚未发现的顶点
        if (UNDISCOVERED == status(v)) BFS(v, clock);  //即从该顶点出发启动一次BFS
    while (s != (v = ((v + 1) % n)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(Rank v, int &clock) { //v < n
    Queue<Rank> Q; //引入辅助队列
    status(v) = DISCOVERED;
    Q.enqueue(v); //初始化起点
    while (!Q.empty()) { //在Q变空之前，不断
        Rank r = Q.dequeue();
        dTime(r) = ++clock; //取出队首顶点v
        for (Rank u = firstNbr(r); -1 < u; u = nextNbr(r, u)) //枚举v的所有邻居u
            if (UNDISCOVERED == status(u)) { //若u尚未被发现，则
                status(u) = DISCOVERED;
                Q.enqueue(u); //发现该顶点
                type(r, u) = TREE;
                parent(u) = r; //引入树边拓展支撑树
            } else { //若u已被发现，或者甚至已访问完毕，则
                type(r, u) = CROSS; //将(r, u)归类于跨边
            }
        status(r) = VISITED; //至此，当前顶点访问完毕
    }
}

template<typename Tv, typename Te>
struct BfsPU { //针对BFS算法的顶点优先级更新器
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v) {
        if (g->status(v) == UNDISCOVERED) //对于uk每一尚未被发现的邻接顶点v
            if (g->priority(v) > g->priority(uk) + 1) { //将其到起点的距离作为优先级数
                g->priority(v) = g->priority(uk) + 1; //更新优先级（数）
                g->parent(v) = uk; //更新父节点
            } //如此效果等同于，先被发现者优先
    }
};

#endif //DSA_GRAPH_REALIZATION_H
