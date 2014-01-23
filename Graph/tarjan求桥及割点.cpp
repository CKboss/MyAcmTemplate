/*
求割点，去掉割点连通块的个数
求桥
*/
const int maxV=10010,maxE=100010;

struct Edge
{
    int to,next;
    bool cut;
}edge[maxE];

int Adj[maxV],Size;

void init()
{
    Size=0;
    memset(Adj,-1,sizeof(Adj));
}

void Add_Edge(int u,int v)
{
    edge[Size].to=v;
    edge[Size].next=Adj[u];
    edge[Size].cut=false;
    Adj[u]=Size++;
}

int Low[maxV],DFN[maxV],Stack[maxV];
int Index,top,bridge;
bool Instack[maxV],cut[maxV];
int add_block[maxV];

void Tarjan(int u,int pre)
{
    int v;
    Low[u]=DFN[u]=++Index;
    Stack[top++]=u;
    Instack[u]=true;
    int son=0;
    for(int i=Adj[u];~i;i=edge[i].next)
    {
        v=edge[i].to;
        if(v==pre) continue;
        if(!DFN[v])
        {
            son++;
            Tarjan(v,u);
            Low[u]=min(Low[u],Low[v]);

            if(Low[v]>DFN[u])//bridge
            {
                bridge++;
                edge[i].cut=edge[i^1].cut=true;
            }
            
            /*
            两种割点：1. 不是根节点，2.根节点，但是孩子数大于1
            */

            if(u!=pre&&Low[v]>=DFN[u])//cut_point
            {
                cut[u]=true;
                add_block[u]++;
            }
        }
        else
        {
            Low[u]=min(Low[u],DFN[v]);
        }
    }

    if(u==pre&&son>1) cut[u]=true;
    if(u==pre) add_block[u]=son-1;

    Instack[u]=false; top--;
}

int n;

void solve(int n)
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,false,sizeof(Instack));
    memset(add_block,0,sizeof(add_block));
    memset(cut,false,sizeof(cut));

    Index=top=bridge=0;

    for(int i=1;i<=n;i++)
    {
        if(!DFN[i]) Tarjan(i,i);
    }
}
