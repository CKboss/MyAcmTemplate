
//////表示最大费用最大流要改动的地方  SPFA部分，加边和结果都不需要将值取反

struct Edge
{
	int to,next,cap,flow,cost;
}edge[maxn];

int Adj[maxn],Size,N;

void init()
{
	memset(Adj,-1,sizeof(Adj)); Size=0;
}

void addedge(int u,int v,int cap,int cost)
{
	edge[Size].to=v;
	edge[Size].next=Adj[u];
	edge[Size].cost=cost;
	edge[Size].cap=cap;
	edge[Size].flow=0;
	Adj[u]=Size++;
}

void Add_Edge(int u,int v,int cap,int cost)
{
	addedge(u,v,cap,cost);
	addedge(v,u,0,-cost);
}

int dist[1000],vis[1000],pre[1000];

bool spfa(int s,int t)
{
	queue<int> q;
	for(int i=0;i<N;i++)
	{
		dist[i]=INF;vis[i]=false; pre[i]=-1;///////////
	}
	dist[s]=0; vis[s]=true; q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=Adj[u];~i;i=edge[i].next)
		{
			int v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&
				dist[v]>dist[u]+edge[i].cost)/////////
			{
				dist[v]=dist[u]+edge[i].cost;
				pre[v]=i;
				if(!vis[v])
				{
					vis[v]=true;
					q.push(v);
				}
			}
		}
	}
	if(pre[t]==-1) return false;
	return true;
}

int MinCostMaxFlow(int s,int t,int& cost)
{
	int flow=0;
	cost=0;
	while(spfa(s,t))
	{
		int Min=INF;
		for(int i=pre[t];~i;i=pre[edge[i^1].to])
		{
			if(Min>edge[i].cap-edge[i].flow)
				Min=edge[i].cap-edge[i].flow;
		}
		/////不要求满流而只求费用最值的话,在这里判断dist[t]的值并停下来
		for(int i=pre[t];~i;i=pre[edge[i^1].to])
		{
			edge[i].flow+=Min;
			edge[i^1].flow-=Min;
			cost+=edge[i].cost*Min;
		}
		flow+=Min;
	}
	return flow;
}


