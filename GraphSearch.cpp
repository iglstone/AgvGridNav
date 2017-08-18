#include "GraphSearch.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>

#define INTMAX 65535

GraphSearch::GraphSearch()
{
    vexsPre2DTabel preTable = {0};
    distancesSum2DTabel disSumTable = {0};
    vexAngels angels = {0};

    this->InitGraph(&m_graph, XNUM, YNUM);

    this->FloydShortestPath(&m_graph, &preTable, &disSumTable);

    string path = this->FindShortestPath(&m_graph, 13, 7, &preTable, &angels);
    std::cout << path << std::endl;


//    12--13--14--15
//    |   |   |   |
//    8 --9 --10--11
//    |   |   |   |
//    4 --5 --6 --7
//    |   |   |   |
//    0 --1 --2 --3

    //test 0-15 path
    this->PrintShortestPath(&m_graph, &preTable, &disSumTable);

}

void GraphSearch::UpdateGraphWeights(SGraph *gragh, int point0, int point1)
{
    int weight = gragh ->edges[point0][point1].weight;
    if (weight == INTMAX) {
        printf("start and end point not in passed by");
        return;
    }
    gragh->edges[point0][point1].weight = INTMAX;//反方向给堵住
    gragh->edges[point1][point0].weight = INTMAX;//反方向给堵住

    //gragh.weightAndAngels[end][start].weight = INTMAX;//反方向给堵住
}

string GraphSearch::FindShortestPath(SGraph *graph, int start, int end, vexsPre2DTabel *vexPreTabel, vexAngels *angels)
{
    int pointIndexFirst =  (*vexPreTabel)[start][end];//robot.pointNum;
    int angelOfStart = graph->edges[start][pointIndexFirst].angel;
    printf("%d -> (%d)%d -> ",start, angelOfStart, pointIndexFirst);

    std::ostringstream ostr;
    ostr << start <<" -> (" << angelOfStart <<")" << pointIndexFirst << " -> (";

    while (pointIndexFirst != end)
    {
        int pointIndexSaveFirst = pointIndexFirst;
        pointIndexFirst = (*vexPreTabel)[pointIndexFirst][end];     // get next vertex
        int angelOfFirst = graph->edges[pointIndexSaveFirst][pointIndexFirst].angel;    //turn angel , not final angel

        printf("(%d)%d -> ",angelOfFirst, pointIndexFirst);
        ostr << angelOfFirst << ")" << pointIndexFirst << " -> (" ;
    }
    printf("endAngel : %f \n", (*angels)[end]);
    ostr << "AngelsEnd:" << (*angels)[end] << ")" << std::endl;

    string tem = ostr.str();

    return tem;
}

void GraphSearch::PrintShortestPath(SGraph *graph, vexsPre2DTabel *vexPreTable, distancesSum2DTabel *distancesSumTable)
{
    int v,w,k;
    //    for (v  = 0; v < graph->numVertexes; v++) {
    for (v  = 0; v < 1; v++) //测试从0到任意一点
    {
        for (w = v+1; w < graph->numVertexes; w++)
        {
            printf("%d -> %d(length:%d), ",v,w,(*distancesSumTable)[v][w]);
            k = (*vexPreTable)[v][w];       //get the first point
            printf("path: %d",v);        // log sorce point
            while (k != w)
            {
                printf("-> %d ",k);       // log vertex
                k = (*vexPreTable)[k][w];   //get next vertex point
            }
            printf("-> %d \n",w);           // log final point
        }
    }
}

bool GraphSearch::FloydShortestPath(SGraph *graph, vexsPre2DTabel *pointsPreTable, distancesSum2DTabel *distancesSumTable)
{
    int v,w,k;

    for (v = 0; v < graph->numVertexes; v++) // init points distances
    {
        for (w = 0; w < graph->numVertexes; w ++)
        {
            if(graph->edges[v][w].weight == 0)
            {
                continue;
            }
            (*distancesSumTable)[v][w] = graph->edges[v][w].weight;  //distances[v][w]为对应的权值
            (*pointsPreTable)[v][w] = w;  //初始化points
        }
    }

    for (k = 0; k < graph->numVertexes; k++)
    {
        for (v = 0; v < graph->numVertexes; v++)
        {
            for (w = 0; w < graph->numVertexes; w++)
            {
                if(v == w) continue;

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
        for(int j = 0; j < graph->numVertexes ; j++)
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
                graph->edges[i][j].weight = INTMAX;
                graph->edges[i][j].angel = 1;
                graph->edges[j][i].weight = INTMAX;
                graph->edges[j][i].angel = 1;
            }
        }
    }

    for(int i = 0; i < graph->numVertexes; i++)
    {
        for(int j = 0; j < graph->numVertexes; j++)
        {
            if(i == j)
            {
                continue;
            }
            SPointXY point1 = graph->vertex[i];
            SPointXY point0 = graph->vertex[j];
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
    }

    return true;

}
