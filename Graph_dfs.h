//
// Created by zlysm on 11/3/22.
//

#ifndef DSA_GRAPH_DFS_H
#define DSA_GRAPH_DFS_H

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(Rank s) { //s < n
    reset();
    int clock = 0;
    Rank v = s;
    do  //一旦遇到尚未发现的顶点
        if (UNDISCOVERED == status(v)) DFS(v, clock); //即从该顶点出发启动一次DFS
    while (s != (v = ((v + 1) % n))); //按序号检查，故不漏不重
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(Rank v, int &clock) { //v < n
    dTime(v) = ++clock;
    status(v) = DISCOVERED; //发现当前顶点v
    for (Rank u = firstNbr(v); -1 < u; u = nextNbr(v, u)) //枚举v的所有邻居u
        switch (status(u)) { //并视其状态分别处理
            case UNDISCOVERED: //u尚未发现，意味着支撑树可在此拓展
                type(v, u) = TREE;
                parent(u) = v;
                DFS(u, clock);
                break;
            case DISCOVERED: //u已被发现但尚未访问完毕，应属被后代指向的祖先
                type(v, u) = BACKWARD;
                break;
            default: //u已访问完毕（VISITED，有向图），则视承袭关系分为前向边或跨边
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    status(v) = VISITED;
    fTime(v) = ++clock; //至此，当前顶点v方告访问完毕
}

template<typename Tv, typename Te>
struct DfsPU { //针对DFS算法的顶点优先级更新器
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v) {
        if (g->status(v) == UNDISCOVERED) //对于uk每一尚未被发现的邻接顶点v
            if (g->priority(v) > g->priority(uk) - 1) { //将其到起点距离的负数作为优先级数
                g->priority(v) = g->priority(uk) - 1; //更新优先级（数）
                g->parent(v) = uk; //更新父节点
                return; //注意：与BfsPU()不同，这里只要有一个邻接顶点可更新，即可立即返回
            } //如此效果等同于，后被发现者优先
    }
};

#endif //DSA_GRAPH_DFS_H
