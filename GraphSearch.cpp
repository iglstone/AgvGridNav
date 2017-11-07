#include "GraphSearch.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <mutex>

#define INTMAX          65535
#define WEIGHT_HEAVY    4
#define WEIGHT_NORMAL   1
#define WEIGHT_LIGHT    1
#define WEIGHT_ZERO     0

std :: mutex mtx;

carNavAlgrithm::carNavAlgrithm()
{
//    vexsPre2DTable vexPreTable = {0};
//    distancesSum2DTable distancesSumTable = {0};
//    vexAngels finalAngels = {0};

//    this->vexPreTable = {0};
//    this->distancesSumTable = {0};
//    this->finalAngels = {0};

    memset(vexPreTable,0,sizeof(vexPreTable));
    memset(distancesSumTable,0,sizeof(distancesSumTable));
    memset(finalAngels,10,sizeof(finalAngels));
    //finalAngels = {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50};

    this->InitGraph(&m_graph, XNUM, YNUM);

    this->FloydShortestPath(&m_graph, &vexPreTable, &distancesSumTable);
//    this->DijkstraShortestPath(&m_graph, 1, 11);

    // use like this:
    string path = this->FindShortestPath( 1, 11);
    std::cout << path << std::endl;

//    12--13--14--15
//    |   |   |   |
//    8 --9 --10--11
//    |   |   |   |
//    4 --5 --6 --7
//    |   |   |   |
//    0 --1 --2 --3

    //test 0-final path
//    this->PrintShortestPath(&m_graph, &vexPreTable, &distancesSumTable);

}

bool carNavAlgrithm::UpdateGraphWeights(int vexP0, bool heavy)
{
    if (!mtx.try_lock())
    {
        return false;
    }
    if(heavy)
    {
        HeavyGraphWeights(vexP0);
    }
    else
    {
        LightGraphWeights(vexP0);
    }
    mtx.unlock();
    return true;
}

void carNavAlgrithm::HeavyGraphWeights(int vexP0)
{
    int x = m_graph.vertex[vexP0].xLineIndex;
    int y = m_graph.vertex[vexP0].yLineIndex;

    int p1 = x + 1;
    if(p1 <= XNUM)
    {
        int vexP1 = p1 + y * XNUM;
        m_graph.edges[vexP0][vexP1].weight = WEIGHT_HEAVY;
        m_graph.edges[vexP1][vexP0].weight = WEIGHT_HEAVY;
    }

    int p2 = y + 1;
    if(p2 <= YNUM)
    {
        int vexP2 = p2 + y * XNUM;
        m_graph.edges[vexP0][vexP2].weight = WEIGHT_HEAVY;
        m_graph.edges[vexP2][vexP0].weight = WEIGHT_HEAVY;
    }

    int p3 = x - 1;
    if(p3 >= 0)
    {
        int vexP3 = p3 + y * XNUM;
        m_graph.edges[vexP0][vexP3].weight = WEIGHT_HEAVY;
        m_graph.edges[vexP3][vexP0].weight = WEIGHT_HEAVY;
    }

    int p4 = y - 1;
    if(p4 >= 0)
    {
        int vexP4 = p4 + y * XNUM;
        m_graph.edges[vexP0][vexP4].weight = WEIGHT_HEAVY;
        m_graph.edges[vexP4][vexP0].weight = WEIGHT_HEAVY;
    }
}

void carNavAlgrithm::LightGraphWeights(int vexP0)
{
    int x = m_graph.vertex[vexP0].xLineIndex;
    int y = m_graph.vertex[vexP0].yLineIndex;

    int p1 = x + 1;
    if(p1 <= XNUM)
    {
        int vexP1 = p1 + y * XNUM;
        m_graph.edges[vexP0][vexP1].weight = WEIGHT_NORMAL;
        m_graph.edges[vexP1][vexP0].weight = WEIGHT_NORMAL;
    }

    int p2 = y + 1;
    if(p2 <= YNUM)
    {
        int vexP2 = p2 + y * XNUM;
        m_graph.edges[vexP0][vexP2].weight = WEIGHT_NORMAL;
        m_graph.edges[vexP2][vexP0].weight = WEIGHT_NORMAL;
    }

    int p3 = x - 1;
    if(p3 >= 0)
    {
        int vexP3 = p3 + y * XNUM;
        m_graph.edges[vexP0][vexP3].weight = WEIGHT_NORMAL;
        m_graph.edges[vexP3][vexP0].weight = WEIGHT_NORMAL;
    }

    int p4 = y - 1;
    if(p4 >= 0)
    {
        int vexP4 = p4 + y * XNUM;
        m_graph.edges[vexP0][vexP4].weight = WEIGHT_NORMAL;
        m_graph.edges[vexP4][vexP0].weight = WEIGHT_NORMAL;
    }
}

void carNavAlgrithm::UpdateGraphWeights(SGraph *gragh, int point0, int point1)
{
    int weight = gragh ->edges[point0][point1].weight;
    if (weight == INTMAX) {
        printf("start and end point not in passed by");
        return;
    }
    gragh->edges[point0][point1].weight = WEIGHT_HEAVY;//反方向给堵住
    gragh->edges[point1][point0].weight = WEIGHT_HEAVY;//反方向给堵住

    //gragh.weightAndAngels[end][start].weight = INTMAX;//反方向给堵住
}

string carNavAlgrithm::FindShortestPath(int start, int end)
{
    int pointIndexFirst =  vexPreTable[start][end];//robot.pointNum;
    int angelOfStart = m_graph.edges[start][pointIndexFirst].angel;
    //printf("%d -> (%d)%d -> ",start, angelOfStart, pointIndexFirst);

    ostringstream ostr;
    ostr << start <<"." << angelOfStart <<" -> " << pointIndexFirst << ".";

    while (pointIndexFirst != end)
    {
        int pointIndexSaveFirst = pointIndexFirst;
        pointIndexFirst = vexPreTable[pointIndexFirst][end];     // get next vertex
        int angelOfFirst = m_graph.edges[pointIndexSaveFirst][pointIndexFirst].angel;    //turn angel , not final angel

        //printf("(%d)%d -> ",angelOfFirst, pointIndexFirst);
        ostr << angelOfFirst << " -> " << pointIndexFirst << "." ;
    }
    //printf("endAngel : %f \n", (finalAngels)[end]);
    ostr << (finalAngels)[end] << std::endl;

    string tem = ostr.str();

    return tem;
}

//string GraphSearch::FindShortestPath(int start, int end)
//{
//    int pointIndexFirst =  vexPreTable[start][end];//robot.pointNum;
//    int angelOfStart = m_graph.edges[start][pointIndexFirst].angel;
//    printf("%d -> (%d)%d -> ",start, angelOfStart, pointIndexFirst);

//    ostringstream ostr;
//    ostr << start <<" -> (" << angelOfStart <<")" << pointIndexFirst << " -> (";

//    while (pointIndexFirst != end)
//    {
//        int pointIndexSaveFirst = pointIndexFirst;
//        pointIndexFirst = vexPreTable[pointIndexFirst][end];     // get next vertex
//        int angelOfFirst = m_graph.edges[pointIndexSaveFirst][pointIndexFirst].angel;    //turn angel , not final angel

//        printf("(%d)%d -> ",angelOfFirst, pointIndexFirst);
//        ostr << angelOfFirst << ")" << pointIndexFirst << " -> (" ;
//    }
//    printf("endAngel : %f \n", (finalAngels)[end]);
//    ostr << "AngelsEnd:" << (finalAngels)[end] << ")" << std::endl;

//    string tem = ostr.str();

//    return tem;
//}

void carNavAlgrithm::DijkstraShortestPath(SGraph *graph, int start, int end)
{
    int vexMaxNum = graph->numVertexes;
    bool S[vexMaxNum]; // 判断是否已存入该点到S集合中
    int prev[vexMaxNum];
    int  n = vexMaxNum;
    int dist[vexMaxNum];

    for(int i = 0; i < vexMaxNum; i++)
    {
        dist[i] = graph->edges[start][i].weight;
        S[i] = false; // 初始都未用过该点
        if(dist[i] == INTMAX || dist[i] == WEIGHT_ZERO)
            prev[i] = -1;
        else
            prev[i] = start;
    }

    dist[start] = 0;
    S[start] = true;

    for(int i = 0; i < n; i++)
    {
         int mindist = INTMAX;
         int u = start; // 找出当前未使用的点j的dist[j]最小值
         for(int j = 0; j < n; j++)
         {
             if(j == u) continue;
             if((!S[j]) && dist[j] < mindist)
             {
                   u = j; // u保存当前邻接点中距离最小的点的号码
                   mindist = dist[j];
             }
         }

         S[u] = true;

         for(int j=0; j<n; j++)
         {
             if((!S[j]) && graph->edges[u][j].weight < INTMAX && graph->edges[u][j].weight != WEIGHT_ZERO)
             {
                 if(dist[u] + graph->edges[u][j].weight < dist[j])     //在通过新加入的u点路径找到离v0点更短的路径
                 {
                     dist[j] = dist[u] + graph->edges[u][j].weight;    //更新dist
                     prev[j] = u;                    //记录前驱顶点
                     printf(" distances:%d pre:%d ", dist[j], u);
                 }
             }
         }
    }

}

bool carNavAlgrithm::FloydShortestPath(SGraph *graph, vexsPre2DTable *vexPreTable, distancesSum2DTable *distancesSumTable)
{
    if (!mtx.try_lock())
    {
        return false;
    }

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
            (*vexPreTable)[v][w] = w;  //初始化points
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
                    (*vexPreTable)[v][w]    = (*vexPreTable)[v][k];//路径设置为净多下标为k的顶点
                }
            }
        }
    }

    mtx.unlock();
    return true;
}

bool carNavAlgrithm::InitGraph(SGraph *graph, int xMax, int yMax)
{
    graph->numVertexes = xMax * yMax;

    for(int y = 0; y < yMax; y++)
    {
        for(int x = 0; x < xMax; x++)
        {
            graph->vertex[y * xMax + x].xLineIndex = x;
            graph->vertex[y * xMax + x].yLineIndex = y;
        }
    }

    for(int i = 0; i < graph->numVertexes ; i++)
    {
        for(int j = 0; j < graph->numVertexes ; j++)
        {
            if(i == j)
            {
                graph->edges[i][j].weight = WEIGHT_ZERO;
                graph->edges[i][j].angel = ForWord_Self;
                graph->edges[j][i].weight = WEIGHT_ZERO;
                graph->edges[j][i].angel = ForWord_Self;
            }
            else
            {
                graph->edges[i][j].weight = INTMAX;
                graph->edges[i][j].angel = ForWord_Unknow;
                graph->edges[j][i].weight = INTMAX;
                graph->edges[j][i].angel = ForWord_Unknow;
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
            int p00 = x0 + y0 * xMax;
            int p11 = x1 + y1 * xMax;
            int p0 = j ;//x0 + y0 * xMax;
            int p1 = i ;//x1 + y1 * yMax;

            if(p00 != p0 || p11 != p1)
            {
                printf("there is sth wrong!");
            }

            if(x1 - x0 == 1 && y0 - y1 == 0)
            {
                graph->edges[p0][p1].weight = WEIGHT_NORMAL;
                graph->edges[p0][p1].angel = ForWord_Front;
                graph->edges[p1][p0].weight = WEIGHT_NORMAL;
                graph->edges[p1][p0].angel = ForWord_Back;
            }

            if(y1 - y0 == 1 && x0 - x1 == 0)
            {
                graph->edges[p0][p1].weight = WEIGHT_NORMAL;
                graph->edges[p0][p1].angel = ForWord_Up;
                graph->edges[p1][p0].weight = WEIGHT_NORMAL;
                graph->edges[p1][p0].angel = ForWord_Down;
            }
        }
    }

    //test
    //graph->edges[1][2].weight = WEIGHT_HEAVY;
    return true;

}

void carNavAlgrithm::PrintShortestPath(SGraph *graph, vexsPre2DTable *vexPreTable, distancesSum2DTable *distancesSumTable)
{
    int v,w,k;
    //    for (v  = 0; v < graph->numVertexes; v++) {
    for (v  = 0; v < 1; v++) //测试从0到任意一点
    {
        for (w = v+1; w < graph->numVertexes; w++)
        {
            printf("%d -> %d(length:%d), ",v,w,(*distancesSumTable)[v][w]);
            k = (*vexPreTable)[v][w];       // get the first point
            printf("path: %d",v);           // log sorce point
            while (k != w)
            {
                printf("-> %d ",k);         // log vertex
                k = (*vexPreTable)[k][w];   // get next vertex point
            }
            printf("-> %d \n",w);           // log final point
        }
    }
}
