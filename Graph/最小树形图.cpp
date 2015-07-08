/*
朱刘算法 最小树形图:

最小树形图无根树:
建立一个虚拟的根节点,向所有节点连边,权值为其他所有边的权值和+1
在求最小树形图的时候,记录和虚拟的根相连的是哪个节点,模版中边优化就不能用了

//// !!!!为输出路径用
*/


struct Edge
{
	int u,v,cost,id,ru,rv,rcost;
}edge[maxn];

void add_Edge(int id,int u,int v,int c)
{
	edge[id].id=id;
	edge[id].u=edge[id].ru=u;
	edge[id].v=edge[id].rv=v;
	edge[id].cost=edge[id].rcost=c;
}

int pre[maxn],id[maxn],vis[maxn],in[maxn];

//// !!!!
int preid[maxn],useE[maxn];
int eA[maxn],eD[maxn];
int ex;

int zhuliu(int root,int n,int m,Edge edge[])
{
	int ex=m,res=0;
	while(true)
	{
		for(int i=0;i<n;i++) in[i]=INF;
		for(int i=0;i<m;i++)
		{
			if(edge[i].u!=edge[i].v&&edge[i].cost<in[edge[i].v])
			{
				pre[edge[i].v]=edge[i].u;
				in[edge[i].v]=edge[i].cost;

				//// !!!!
				preid[edge[i].v]=edge[i].id;
			}
		}
		for(int i=0;i<n;i++)
			if(i!=root&&in[i]==INF) return -1;
		int tn=0;
		memset(id,-1,sizeof(id));
		memset(vis,-1,sizeof(vis));
		in[root]=0;
		for(int i=0;i<n;i++)
		{
			res+=in[i];
			int v=i;
			//// !!!!
			if(i!=root) useE[preid[i]]++;
			while(vis[v]!=i&&id[v]==-1&&v!=root)
			{
				vis[v]=i; v=pre[v];
			}
			if(v!=root&&id[v]==-1)
			{
				for(int u=pre[v];u!=v;u=pre[u]) id[u]=tn;
				id[v]=tn++;
			}
		}
		if(tn==0) break;
		for(int i=0;i<n;i++)
			if(id[i]==-1) id[i]=tn++;
		for(int i=0;i<m;i++)
		{
			int v=edge[i].v;
			edge[i].u=id[edge[i].u];
			edge[i].v=id[edge[i].v];
			if(edge[i].u!=edge[i].v)
			{
				edge[i].cost-=in[v];
				//// !!!!
				eA[ex]=edge[i].id;
				eD[ex]=preid[v];
				edge[i].id=ex;
				ex++;
			}
		}
		n=tn;
		root=id[root];
	}

	//// !!!!
	for(int i=ex-1;i>=m;i--)
	{
		if(useE[i])
		{
			useE[eA[i]]++; useE[eD[i]]--;
		}
	}

	return res;
}
