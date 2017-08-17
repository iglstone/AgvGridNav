#ifndef GRAPHSEARCH_H
#define GRAPHSEARCH_H

#define XNUM        4
#define YNUM        4

#define NumVertex   (XNUM * YNUM)
#define Edges       (((XNUM-1) * YNUM) + ((YNUM - 1) * XNUM))

enum ForWord{
    ForWord_Self  = 0,
    ForWord_Front = 1,
    ForWord_Up    = 2,
    ForWord_Back  = 3,
    ForWord_Down  = 4
};

typedef struct
{
    int xLineIndex; // X 线的索引
    int yLineIndex; // Y 线的索引

} SPointXY;

typedef struct
{
    float weight; // 连线权重
    float angel;  // 连线在空间的角度

} SWeightAngel;

typedef struct
{
    SPointXY vertex[NumVertex];
    SWeightAngel edges[NumVertex][NumVertex];
    int numVertexes;

} SGraph;

typedef int     vexsPre2DTabel[NumVertex][NumVertex];//路径前驱下标列表
typedef int     distancesSum2DTabel[NumVertex][NumVertex];//两点间最短路径“和“值列表
typedef float   vexAngels[NumVertex];

class GraphSearch
{
public:
    GraphSearch();
    void PreventTheWay(SGraph *gragh, int start, int end);
    void PrintShortestPath(SGraph *graph, vexsPre2DTabel *vexPreTable, distancesSum2DTabel *distancesSumTable);
    void FindShortestPath(SGraph *graph, int start, int end, vexsPre2DTabel *vexPres, vexAngels *angels);
    bool FloyeShortestPath(SGraph *graph, vexsPre2DTabel *points2, distancesSum2DTabel *distances2);
    bool InitGraph(SGraph *graph, int xMax, int yMax);

private:
    SGraph *graph;
};

#endif // FLOYD_H
