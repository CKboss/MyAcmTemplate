/*
  强连通分量个数tarjan算法
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxV=1000,maxE=1000000;

struct Edge
{
	int to,next;
}edge[maxE];

int Adj[maxV],Size;

void init()
{
	Size=0;
	memset(Adj,-1,sizeof(Adj));
}

void Add_Edge(int u,int v)
{
	edge[Size].to=v; edge[Size].next=Adj[u]; Adj[u]=Size++;
}

int Low[maxV],DFN[maxV],Stack[maxV],Belong[maxV];
int Index,top,scc,n;

bool Instack[maxV]; int num[maxV];

void tarjan(int u)
{
	int v;
	Low[u]=DFN[u]=++Index;
	Stack[top++]=u;
	Instack[u]=true;
	for(int i=Adj[u];~i;i=edge[i].next)
	{
		v=edge[i].to;
		if(!DFN[v])
		{
			tarjan(v);
			Low[u]=min(Low[u],Low[v]);
		}
		else if(Instack[v]) //判断一下那些没有构成联通分量的结点
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
			Instack[v]=false;
			num[scc]++;
			Belong[v]=scc;
		}while(v!=u);
	}
}

void solve(int n)
{
	memset(DFN,0,sizeof(DFN));
	memset(Instack,false,sizeof(Instack));
	memset(num,0,sizeof(num));

	Index=scc=top=0;

	for(int i=1;i<=n;i++)
	{
		if(!DFN[i]) tarjan(i);
	}
}

int main()
{
    int m;
while(scanf("%d%d",&n,&m)!=EOF&&n)
{
    init();
    int a,b;
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&a,&b);
        Add_Edge(a,b);
    }

    solve(n);

    cout<<"scc: "<<scc<<endl;

    for(int i=1;i<=scc;i++) cout<<num[i]<<"--";
    cout<<endl;

    for(int i=1;i<=n;i++)
    {
        cout<<"DFN: "<<DFN[i]<<" , Low: "<<Low[i]<<"     "<<Belong[i]<<endl;
    }
    cout<<endl;
}
	return 0;
}

