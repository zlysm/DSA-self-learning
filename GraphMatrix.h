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

    Vertex(Tv const &d = (Tv) 0) :  //构造新顶点
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

#endif //DSA_GRAPHMATRIX_H
