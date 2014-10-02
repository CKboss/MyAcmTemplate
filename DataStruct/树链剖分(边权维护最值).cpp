
/*
  树链剖分+线段树
维护两点建路径上的边权最大值。。。
SPOJ QTREE
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long int LL;

const int maxn=110000;

struct Edge
{
	int to,next;
}edge[maxn*4];

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
	memset(son,-1,sizeof(son));
	pos=1;
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
			son[u]=v;
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

int n;
int e[maxn][3];

///segTree
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int maxnum[maxn<<2];

void build(int l,int r,int rt)
{
    maxnum[rt]=0;
    if(l==r) return ;
    int m=(l+r)/2;
    build(lson);
    build(rson);
}

void push_up(int rt)
{
    maxnum[rt]=max(maxnum[rt<<1],maxnum[rt<<1|1]);
}

void update(int pos,int val,int l,int r,int rt)
{
    if(l==pos&&r==pos)
    {
        maxnum[rt]=val;
        return ;
    }
    int m=(l+r)/2;
    if(pos<=m) update(pos,val,lson);
    else update(pos,val,rson);
    push_up(rt);
}

int query(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)
    {
        return maxnum[rt];
    }
    int m=(l+r)/2;
    int ret=0;
    if(L<=m) ret=max(ret,query(L,R,lson));
    if(R>m) ret=max(ret,query(L,R,rson));
    return ret;
}

int find(int u,int v)
{
    int f1=top[u],f2=top[v];
    int ret=0;
    while(f1!=f2)
    {
        if(deep[f1]<deep[f2])
        {
            swap(f1,f2); swap(u,v);
        }
        ret=max(ret,query(p[f1]-1,p[u]-1,1,n,1));
        u=fa[f1]; f1=top[u];
    }
    if(u==v) return ret;
    if(deep[u]>deep[v]) swap(u,v);
    ret=max(ret,query(p[son[u]]-1,p[v]-1,1,n,1));
    return ret;
}

void showit(int l,int r,int rt)
{
    cout<<rt<<": "<<l<<" <---> "<<r<<"  max: "<<maxnum[rt]<<endl;
    if(l==r) return ;
    int m=(l+r)/2;
    showit(lson); showit(rson);
}

int main()
{
    int T_T;
    scanf("%d",&T_T);
    while(T_T--)
    {
        scanf("%d",&n);
        init();
        n--;
        for(int i=1;i<=n;i++)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            e[i][0]=a;e[i][1]=b;e[i][2]=c;
            add_edge(a,b);
            add_edge(b,a);
        }
        dfs1(1,1,0);
        getPOS(1,1);
        build(1,n,1);
        for(int i=1;i<=n;i++)
        {
            if(deep[e[i][0]]>deep[e[i][1]])
                swap(e[i][0],e[i][1]);
            update(p[e[i][1]]-1,e[i][2],1,n,1);
        }
        char op[10];
        while(scanf("%s",op)!=EOF)
        {
            if(op[0]=='Q')
            {
                int a,b;
                scanf("%d%d",&a,&b);
                printf("%d\n",find(a,b));
            }
            else if(op[0]=='C')
            {
                int a,b;
                scanf("%d%d",&a,&b);
                update(p[e[a][1]]-1,b,1,n,1);
            }
            else if(op[0]=='D')
            {
                putchar(10);
                break;
            }
        }
    }
	return 0;
}

