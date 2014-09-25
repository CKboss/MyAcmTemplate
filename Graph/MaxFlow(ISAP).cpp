//isap 最大流

const int maxn=50000;
const int maxm=50000000;
const int INF=0x3f3f3f3f;

struct Edge
{
    int to,next,cap,flow;
}edge[maxm];

int Size,Adj[maxn];
int gap[maxn],dep[maxn],pre[maxn],cur[maxn];

void init()
{
    Size=0;
    memset(Adj,-1,sizeof(Adj));
}

void addedge(int u,int v,int w,int rw=0) //单向边3个参数双向边4个
{
    edge[Size].to=v; edge[Size].cap=w; edge[Size].next=Adj[u];
    edge[Size].flow=0; Adj[u]=Size++;
    edge[Size].to=u; edge[Size].cap=rw; edge[Size].next=Adj[v];
    edge[Size].flow=0; Adj[v]=Size++;
}

int sap(int start,int end,int N) //源点 汇点 点的个数
{
    memset(gap,0,sizeof(gap));
    memset(dep,0,sizeof(dep));
    memcpy(cur,Adj,sizeof(Adj));

    int u=start;
    pre[u]=-1; gap[0]=N;
    int ans=0;

    while(dep[start]<N)
    {
        if(u==end)
        {
            int Min=INF;
            for(int i=pre[u];~i;i=pre[edge[i^1].to])
                if(Min>edge[i].cap-edge[i].flow)
                    Min=edge[i].cap-edge[i].flow;
            for(int i=pre[u];~i;i=pre[edge[i^1].to])
            {
                edge[i].flow+=Min;
                edge[i^1].flow-=Min;
            }
            u=start;
            ans+=Min;
            continue;
        }
        bool flag=false;
        int v;
        for(int i=cur[u];~i;i=edge[i].next)
        {
            v=edge[i].to;
            if(edge[i].cap-edge[i].flow&&dep[v]+1==dep[u])
            {
                flag=true;
                cur[u]=pre[v]=i;
                break;
            }
        }
        if(flag)
        {
            u=v;
            continue;
        }
        int Min=N;
        for(int i=Adj[u];~i;i=edge[i].next)
            if(edge[i].cap-edge[i].flow&&dep[edge[i].to]<Min)
            {
                Min=dep[edge[i].to];
                cur[u]=i;
            }
        gap[dep[u]]--;
        if(!gap[dep[u]]) return ans;
        dep[u]=Min+1;
        gap[dep[u]]++;
        if(u!=start) u=edge[pre[u]^1].to;
    }
    return ans;
}

