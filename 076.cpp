#include<cstdio>
#include<cstdlib>
#define INFINITY 65535
#define MaxVertexNum 500
#define ERROR 0
typedef int WeightType;
typedef int MoneyType;
typedef int Vertex;

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;
    WeightType Distance;
    MoneyType Money;
    PtrToAdjVNode Next;
};

typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Distance;
    MoneyType Money;
};
typedef PtrToENode Edge;

typedef struct Vnode
{
    PtrToAdjVNode FirstEdge;
}AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph CreateGraph(int VertexNum, int EdgeNum)
{
    Vertex V;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = EdgeNum;

    for(V=0;V<Graph->Nv;V++)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Money = E->Money;
    NewNode->Distance = E->Distance;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Money = E->Money;
    NewNode->Distance = E->Distance;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph(int VertexNum, int EdgeNum)
{
    LGraph Graph;
    Edge E;

    Graph = CreateGraph(VertexNum, EdgeNum);
    if(Graph->Ne != 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        for(int i=0;i<Graph->Ne;i++)
        {
            scanf("%d %d %d %d", &E->V1, &E->V2, &E->Distance, &E->Money);
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}

Vertex FindMinDist(LGraph Graph, int dist[], int collected[])
{
    Vertex MinV, V;
    int MinDist = INFINITY;

    for (V=0; V<Graph->Nv; V++)
    {
        if ( !collected[V] && dist[V]<MinDist)
        {
            MinDist = dist[V];
            MinV = V;
        }
    }
    if (MinDist < INFINITY)
        return MinV;
    else return ERROR;
}

void Dijkstra(LGraph Graph, int dist[], int money[], Vertex startNode)
{
    int collected[MaxVertexNum];
    PtrToAdjVNode tmp;
    Vertex V;
    for(int i=0;i<Graph->Nv;i++)
        collected[i] = 0;
    collected[startNode] = 1;

    while(1)
    {
        V = FindMinDist(Graph, dist, collected);
        if(V == ERROR)
            break;
        collected[V] = 1;
        tmp = Graph->G[V].FirstEdge;
        while(tmp)
        {

            if(!collected[tmp->AdjV])
                if(dist[V] + tmp->Distance < dist[tmp->AdjV])
                {
                    dist[tmp->AdjV] = dist[V] + tmp->Distance;
                    money[tmp->AdjV] = money[V] + tmp->Money;
                }
            else if((dist[V]+tmp->Distance == dist[tmp->AdjV]) && (money[V]+tmp->Money < money[tmp->AdjV]))
                money[tmp->AdjV] = money[V] + tmp->Money;

            tmp = tmp->Next;
        }
    }
}

void Initialization(LGraph Graph, WeightType dist[], MoneyType money[], Vertex startNode)
{
    PtrToAdjVNode tmp = Graph->G[startNode].FirstEdge;

    for(int i=0;i<MaxVertexNum;i++)
    {
        dist[i] = INFINITY;
        money[i] = INFINITY;
    }
    dist[startNode] = 0;
    money[startNode] = 0;

    while(tmp)
    {
        dist[tmp->AdjV] = tmp->Distance;
        money[tmp->AdjV] = tmp->Money;
        tmp = tmp->Next;
    }
}

int main()
{
    LGraph Graph;
    int VertexNum, EdgeNum;
    Vertex StartNode, EndNode;
    WeightType dist[MaxVertexNum];
    MoneyType money[MaxVertexNum];

    scanf("%d %d %d %d", &VertexNum, &EdgeNum, &StartNode, &EndNode);
    Graph = BuildGraph(VertexNum, EdgeNum);
    Initialization(Graph, dist, money, StartNode);
    Dijkstra(Graph, dist, money, StartNode);

    printf("%d %d", dist[EndNode], money[EndNode]);

    return 0;
}
