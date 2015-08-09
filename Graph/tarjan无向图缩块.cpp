
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <cmath>
#pragma comment(linker, "/STACK:1024000000,1024000000")

using namespace std;

const int maxn=220000;

struct Edge
{
    int from,to,next,id;
}edge[maxn*10];

int Adj[maxn],Size,n,m;

void init()
{
    Size=0;
    memset(Adj,-1,sizeof(Adj));
}

void Add_Edge(int u,int v,int id)
{
    edge[Size].from=u;
    edge[Size].id=id;
    edge[Size].to=v;
    edge[Size].next=Adj[u];
    Adj[u]=Size++;
}

int Low[maxn],DFN[maxn],Stack[maxn],Belong[maxn];
int Index,top,scc;
bool Instack[maxn],vis[maxn],ve[maxn*10];

void Tarjan(int u,int fa)
{
    int v;
    Low[u]=DFN[u]=++Index;
    Stack[top++]=u;
    Instack[u]=true;

    for(int i=Adj[u];~i;i=edge[i].next)
    {
        v=edge[i].to;
        if(v==fa&&ve[edge[i].id]) continue;
        ve[edge[i].id]=true;
        if(!DFN[v])
        {
            Tarjan(v,u);
            Low[u]=min(Low[u],Low[v]);
        }
        else
        {
            Low[u]=min(Low[u],DFN[v]);
        }
    }

    if(Low[u]==DFN[u])
    {
        scc++;
        do
        {
            v=Stack[--top];
            Belong[v]=scc;
            Instack[v]=false;
        }while(v!=u);
    }
}

void scc_solve()
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,0,sizeof(Instack));

    Index=scc=top=0;
    memset(ve,0,sizeof(ve));
    for(int i=1;i<=n;i++)
    {
        if(!DFN[i]) Tarjan(i,i);
    }
}

int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n==0&&m==0) break;
        init();
        for(int i=0;i<m;i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            Add_Edge(a,b,i); Add_Edge(b,a,i);
        }
        scc_solve();
    }
}
