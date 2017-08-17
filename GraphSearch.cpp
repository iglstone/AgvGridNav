#include "GraphSearch.h"
#include <vector>
#include <string>

#define INTMAX 65535

using namespace std;

GraphSearch::GraphSearch()
{
    vexsPre2DTabel *preTable;
    distancesSum2DTabel *disSumTable;
    this->InitGraph(this->graph, XNUM, YNUM);
}

void GraphSearch::PreventTheWay(SGraph *gragh, int start, int end)
{
    int weight = gragh ->edges[start][end].weight;
    if (weight == INTMAX) {
        printf("start and end point not in passed by");
        return;
    }
    gragh->edges[start][end].weight = INTMAX;//反方向给堵住
    //gragh.weightAndAngels[end][start].weight = INTMAX;//反方向给堵住
}

void GraphSearch::FindShortestPath(SGraph *graph, int start, int end, vexsPre2DTabel *vexPreTabel, vexAngels *angels)
{
    int pointIndexFirst =  (*vexPreTabel)[start][end];//robot.pointNum;
    int angelOfStart = graph->edges[start][pointIndexFirst].angel;
    printf("%d,oo,%d", pointIndexFirst, angelOfStart);
    //NSString *tem = [NSString stringWithFormat:@"%d,%d->%d,", start, angelOfStart, pontIndexFirst];

    while (pointIndexFirst != end)
    {
        int pointIndexSaveFirst = pointIndexFirst;
        pointIndexFirst = (*vexPreTabel)[pointIndexFirst][end];// get next vertex point
        int angelOfFirst = graph->edges[pointIndexSaveFirst][pointIndexFirst].angel;//turn angel , not final angel

        printf("%d,xx,%d", pointIndexFirst, angelOfFirst);

        //tem = [tem stringByAppendingString:[NSString stringWithFormat:@"%d->%d,",angelOfFirst, pontIndexFirst]];
    }
    printf("angels end : %f", (*angels)[end]);
    //tem = [tem stringByAppendingString:[NSString stringWithFormat:@"%.0f",(*angels)[end]]];//final angel
    //return tem;
}

void GraphSearch::PrintShortestPath(SGraph *graph, vexsPre2DTabel *vexPreTable, distancesSum2DTabel *distancesSumTable)
{
    int v,w,k;
    //    for (v  = 0; v < graph->numVertexes; v++) {
    for (v  = 0; v < 1; v++) //测试从0到任意一点
    {
        for (w = v+1; w < graph->numVertexes; w++)
        {
            printf("v%d - w%d: weight :%d",v,w,(*distancesSumTable)[v][w]);
            k = (*vexPreTable)[v][w];       //get the first point
            printf("path: %d",v);           // log sorce point
            while (k != w)
            {
                printf("-> %d",k);// log vertex
                k = (*vexPreTable)[k][w];   //get next vertex point
            }
            printf("-> %d",w);              // log final point
        }
    }
}

bool GraphSearch::FloyeShortestPath(SGraph *graph, vexsPre2DTabel *pointsPreTable, distancesSum2DTabel *distancesSumTable)
{
    int v,w,k;

    for (v = 0; v < graph->numVertexes; v++) // init points distances
    {
        for (w = 0; w < graph->numVertexes; w++)
        {
            (*distancesSumTable)[v][w] = graph->edges[v][w].weight;//distances[v][w]为对应的权值
            (*pointsPreTable)[v][w] = w;    //初始化points
        }
    }

    for (k = 0; k < graph->numVertexes; k++)
    {
        for (v = 0; v < graph->numVertexes; v++)
        {
            for (w = 0; w < graph->numVertexes; w++)
            {
                if ((*distancesSumTable)[v][w] > (*distancesSumTable)[v][k] + (*distancesSumTable)[k][w])
                {
                    (*distancesSumTable)[v][w] = (*distancesSumTable)[v][k] + (*distancesSumTable)[k][w];
                    (*pointsPreTable)[v][w]    = (*pointsPreTable)[v][k];//路径设置为净多下标为k的顶点
                }
            }
        }
    }

    return true;
}

bool GraphSearch::InitGraph(SGraph *graph, int xMax, int yMax)
{
    graph->numVertexes = xMax * yMax;

    for(int y = 0; y < yMax; y++)
    {
        for(int x = 0; x < xMax; x++)
        {
            graph->vertex[y*xMax + x].xLineIndex = x;
            graph->vertex[y*xMax + x].yLineIndex = y;
        }
    }

    for(int i = 0; i < graph->numVertexes ; i++)
    {
        for(int j = 0; j < NumVertex; j++)
        {
            if(i == j)
            {
                graph->edges[i][j].weight = 0;
                graph->edges[i][j].angel = ForWord_Self;
                graph->edges[j][i].weight = 0;
                graph->edges[j][i].angel = ForWord_Self;
            }
            else
            {
                graph->edges[i][j].weight = 65535;
                graph->edges[i][j].angel = 1;
                graph->edges[j][i].weight = 65535;
                graph->edges[j][i].angel = 1;
            }
        }
    }

    for(int i = 1; i < graph->numVertexes; i++)
    {
        SPointXY point1 = graph->vertex[i];
        SPointXY point0 = graph->vertex[i-1];
        int x1 = point1.xLineIndex;
        int y1 = point1.yLineIndex;
        int x0 = point0.xLineIndex;
        int y0 = point0.yLineIndex;

        int p0 = x0 + y0 * xMax;
        int p1 = x1 + y1 * yMax;

        if(x1 - x0 == 1 && y0 - y1 == 0)
        {
            graph->edges[p0][p1].weight = 1;
            graph->edges[p0][p1].angel = ForWord_Front;
            graph->edges[p1][p0].weight = 1;
            graph->edges[p1][p0].angel = ForWord_Back;
        }

        if(y1 - y0 == 1 && x0 - x1 == 0)
        {
            graph->edges[p0][p1].weight = 1;
            graph->edges[p0][p1].angel = ForWord_Up;
            graph->edges[p1][p0].weight = 1;
            graph->edges[p1][p0].angel = ForWord_Down;
        }
    }

    return true;

}
