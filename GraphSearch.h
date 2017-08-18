#ifndef GRAPHSEARCH_H
#define GRAPHSEARCH_H

#include <string>

#define XNUM        8
#define YNUM        10

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

typedef int     vexsPre2DTable[NumVertex][NumVertex];//路径前驱下标列表
typedef int     distancesSum2DTable[NumVertex][NumVertex];//两点间最短路径“和“值列表
typedef float   vexAngels[NumVertex];

using namespace std;

class GraphSearch
{

public:
    GraphSearch();
    string FindShortestPath( int start, int end);

private:
    void UpdateGraphWeights(SGraph *gragh, int start, int end);
    void PrintShortestPath(SGraph *graph, vexsPre2DTable *vexPreTable, distancesSum2DTable *distancesSumTable);
    //string FindShortestPath(SGraph *graph, int start, int end, vexsPre2DTable *vexPreTable, vexAngels *finalAngels);
    bool FloydShortestPath(SGraph *graph, vexsPre2DTable *vexPreTable, distancesSum2DTable *distancesSumTable);
    bool InitGraph(SGraph *graph, int xMax, int yMax);

private:
    SGraph m_graph;
    vexsPre2DTable vexPreTable ;
    distancesSum2DTable distancesSumTable ;
    vexAngels finalAngels ;
};

#endif // FLOYD_H
