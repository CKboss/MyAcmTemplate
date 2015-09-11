/*
俗称邻接表
*/

#include <iostream>
#include <cstring>
#include <cstdio> 

using namespace std;

const int MaxV=1000;
const int MaxE=10000;

typedef struct node
{
    int to;
    int next;
}Edge;

Edge E[MaxE];
int Adj[MaxV];
int Size;

void Init()
{
    Size=0;
    memset(Adj,-1,sizeof(Adj));
}

void Add_Edge(int u,int v)
{
    E[Size].to=v;
    E[Size].next=Adj[u];
    Adj[u]=Size++;
}

void Show(int u)
{
    for(int i=Adj[u];~i;i=E[i].next)
    {
        printf("%d--->%d\n",u,E[i].to);
    }
}

/// 切掉 u ---> v
void cutUV(int u,int v)
{
	int last=Adj[u];
	for(int i=Adj[u];~i;i=edge[i].next)
	{
		if(edge[i].to==v)
		{
			if(edge[last].next!=edge[i].next) edge[last].next=edge[i].next;
			else Adj[u]=edge[i].next;
		}
		last=i;
	}
}
