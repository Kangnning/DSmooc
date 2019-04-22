#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 10

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    int AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode
{
    PtrToAdjVNode FirstEdge;
    int Data;
}AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph CreateGraph(int VertexNum, int EdgeNum);
void InsertEdge(LGraph Graph);
void DFS(LGraph Graph, int V, int Visited[]);
void BFS (LGraph Graph, int V, int Visited[]);

int main()
{
    LGraph Graph;
    int N, E, Visited[MaxVertexNum]={0};
    scanf("%d %d", &N, &E);
    Graph = CreateGraph(N, E);

    for(int i=0;i<E;i++)
    {
        InsertEdge(Graph);
    }

    for(int i=0;i<N;i++)
    {
        if(!Visited[i] && i!=0)
            printf("}\n");
        if(!Visited[i])
            printf("{ ");
        DFS(Graph, i, Visited);
    }
    printf("}\n");

    for(int i=0;i<N;i++)
        Visited[i] = 0;
    for(int i=0;i<N;i++)
    {
        if(!Visited[i])
            BFS(Graph, i, Visited);
    }

    return 0;
}

LGraph CreateGraph(int VertexNum, int EdgeNum)
{
    int V;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = EdgeNum;

    for(V=0;V<Graph->Nv;V++)
    {
        Graph->G[V].Data = V;
        Graph->G[V].FirstEdge = NULL;
    }

    return Graph;
}

void InsertEdge(LGraph Graph)
{
    PtrToAdjVNode NewNode, tmp;
    int V1, V2;
    scanf("%d %d", &V1, &V2);

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = V2;

    //插入边并且按照结点从小到大排列
    tmp = Graph->G[V1].FirstEdge;
    if(!tmp)                                                //FirstEdge为空的情况
    {
        NewNode->Next = tmp;
        Graph->G[V1].FirstEdge = NewNode;
    }
    else if(tmp->AdjV > NewNode->AdjV && !tmp->Next)        //只有一个FirstEdge且FirstEdge的值大于新插入的NewNode的值
    {
        NewNode->Next = tmp;
        Graph->G[V1].FirstEdge = NewNode;
    }
    else if(tmp->AdjV > NewNode->AdjV)                      //有多个相邻点
    {
        while(tmp->AdjV < NewNode->AdjV && tmp->Next)
            tmp = tmp->Next;
        NewNode->Next = tmp->Next;
        tmp->Next = NewNode;
    }
    else if(tmp->AdjV < NewNode->AdjV && !tmp->Next)        //只有一个相邻点且新插入的值大于相邻点
    {
        NewNode->Next = NULL;
        tmp->Next = NewNode;
    }
    else                                                  //含有多个相邻点且第一个相邻点小于新插入的值
    {
        while(tmp->Next && tmp->Next->AdjV < NewNode->AdjV)
                tmp = tmp->Next;
        NewNode->Next = tmp->Next;
        tmp->Next = NewNode;
    }

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = V1;

    tmp = Graph->G[V2].FirstEdge;
    if(!tmp)                                                //FirstEdge为空的情况
    {
        NewNode->Next = tmp;
        Graph->G[V2].FirstEdge = NewNode;
    }
    else if(tmp->AdjV > NewNode->AdjV && !tmp->Next)        //只有一个FirstEdge且FirstEdge的值大于新插入的NewNode的值
    {
        NewNode->Next = tmp;
        Graph->G[V2].FirstEdge = NewNode;
    }
    else if(tmp->AdjV > NewNode->AdjV)                      //有多个相邻点
    {
        while(tmp->AdjV < NewNode->AdjV && tmp->Next)
            tmp = tmp->Next;
        NewNode->Next = tmp->Next;
        tmp->Next = NewNode;
    }
    else if(tmp->AdjV < NewNode->AdjV && !tmp->Next)        //只有一个相邻点且新插入的值大于相邻点
    {
        NewNode->Next = NULL;
        tmp->Next = NewNode;
    }
    else                                                  //含有多个相邻点且第一个相邻点小于新插入的值
    {
        while(tmp->Next && tmp->Next->AdjV < NewNode->AdjV)
            tmp = tmp->Next;
        NewNode->Next = tmp->Next;
        tmp->Next = NewNode;
    }
}

void DFS(LGraph Graph, int V, int Visited[])
{
    PtrToAdjVNode W;

    if(!Visited[V])
        printf("%d ", Graph->G[V].Data);
    Visited[V] = 1;

    for(W=Graph->G[V].FirstEdge; W; W=W->Next)
        if (!Visited[W->AdjV])
            DFS(Graph, W->AdjV, Visited);
}

void BFS (LGraph Graph, int V, int Visited[])
{
    PtrToAdjVNode tmp;
    int que[MaxVertexNum];
    for(int i=0;i<MaxVertexNum;i++)
        que[i] = -1;

    int Front, Rear;
    Front = -1;
    Rear = 0;

    Front++;
    que[Front] = V;
    Visited[que[Front]] = 1;

    printf("{ ");
    while(Rear - Front != 1)
    {
        printf("%d ", Graph->G[que[Rear]].Data);
        tmp = Graph->G[que[Rear]].FirstEdge;
        Rear++;
        while(tmp)
        {
            if(!Visited[tmp->AdjV])
            {
                Front++;
                que[Front] = tmp->AdjV;
                Visited[que[Front]] = 1;
            }
            tmp = tmp->Next;
        }
    }
    printf("}\n");
}
