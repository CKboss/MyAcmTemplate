/*
树链剖分+树状数组 维护路径上的点/边
HDOJ3966
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn=100500;

struct Edge
{
    int to,next;
}edge[maxn];

int Adj[maxn],Size;

void init_edge()
{
    memset(Adj,-1,sizeof(Adj)); Size=0;
}

void add_edge(int u,int v)
{
    edge[Size].to=v; edge[Size].next=Adj[u]; Adj[u]=Size++;
}

int fa[maxn],deep[maxn],num[maxn],son[maxn];
int top[maxn],p[maxn],rp[maxn],pos;

// fa 父节点 deep 深度 num 孩子数 son 重儿子
// top 链顶点 p 再数据结构中位置 rp p的反 

void init()
{
    init_edge();
    memset(son,-1,sizeof(son)); pos=1;
}

void dfs1(int u,int pre,int d)
{
    num[u]=1; fa[u]=pre; deep[u]=d;
    for(int i=Adj[u];~i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v==pre) continue;
        dfs1(v,u,d+1);
        num[u]+=num[v];
        if(son[u]==-1||num[son[u]]<num[v])
        {
            son[u]=v;
        }
    }
}

void getPOS(int u,int to)
{
    top[u]=to;
    p[u]=pos++;
    rp[p[u]]=u;
    if(son[u]!=-1) getPOS(son[u],to);
    for(int i=Adj[u];~i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v!=fa[u]&&v!=son[u])
            getPOS(v,v);
    }
}

int tree[maxn];
int n,m,q;

inline int lowbit(int x)
{
    return x&(-x);
}

void ADD(int p,int v)
{
    for(int i=p;i<=n;i+=lowbit(i))
        tree[i]+=v;
}

int SUM(int p)
{
    int ret=0;
    for(int i=p;i;i-=lowbit(i))
        ret+=tree[i];
    return ret;
}
    

void Change(int u,int v,int K)
{
    int f1=top[u],f2=top[v];
    while(f1!=f2)
    {
        if(deep[f1]<deep[f2])
        {
            swap(f1,f2);
            swap(u,v);
        }
        ADD(p[f1],K);
        ADD(p[u]+1,-K);
        u=fa[f1];
        f1=top[u];
    }
    if(deep[u]<deep[v]) swap(u,v);
    ADD(p[v],K);
    ADD(p[u]+1,-K);
}

int a[maxn];

int main()
{
    //freopen("in.txt","r",stdin);
    while(scanf("%d%d%d",&n,&m,&q)!=EOF)
    {
        init();
        for(int i=1;i<=n;i++)
            scanf("%d",a+i);
        while(m--)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            add_edge(a,b);
            add_edge(b,a);
        }
        dfs1(1,-1,0);
        getPOS(1,1);
        memset(tree,0,sizeof(tree));
        for(int i=1;i<=n;i++)
        {
            ADD(p[i],a[i]);
            ADD(p[i]+1,-a[i]);
        }
        char ord;
        int a,b,c;
        while(q--)
        {
            scanf("%*c %c",&ord);
            if(ord=='Q')
            {
                scanf("%d",&a);
                printf("%d\n",SUM(p[a]));
            }
            else
            {
                scanf("%d%d%d",&a,&b,&c);
                if(ord=='D') c=-c;
                Change(a,b,c);
            }
        }
    }
    return 0;
}


//边权维护
void Change2(int u,int v,int k)  
{  
    int f1=top[u],f2=top[v];  
    while(f1!=f2)  
    {  
        if(deep[f1]<deep[f2])  
        {  
            swap(f1,f2); swap(u,v);  
        }  
        ADD(1,p[f1]-1,k); ADD(1,p[u],-k);  
        u=fa[f1]; f1=top[u];  
    }  
    if(u==v) return ;  
    if(deep[u]<deep[v]) swap(u,v);  
    ADD(1,p[son[v]]-1,k);  
    ADD(1,p[u],-k);  
}  

