/*
by KuangBin
更快的最大流模板
sap
*/
const int INF=0x3f3f3f3f;
const int maxm=1001000;
const int maxn=1005;

struct Edge
{
	int from,to,next;
	int cap;
}edge[maxm];

int Size;
int Adj[maxn],dep[maxn],gap[maxn];

int S,T,N;/// N总点数 

void init()
{
	Size=0; memset(Adj,-1,sizeof(int)*N);
}

void addedge(int u,int v,int w)
{
	edge[Size].from=u; edge[Size].to=v;
	edge[Size].cap=w; edge[Size].next=Adj[u];
	Adj[u]=Size++;

	edge[Size].from=v; edge[Size].to=u;
	edge[Size].cap=0; edge[Size].next=Adj[v];
	Adj[v]=Size++;
}

void BFS(int start,int end)
{
	memset(dep,-1,sizeof(int)*(N+10));
	memset(gap,0,sizeof(int)*(N+10));
	gap[0]=1;
	int que[maxn];
	int front,rear;
	front=rear=0; dep[end]=0;
	que[rear++]=end;
	while(front!=rear)
	{
		int u=que[front++];
		if(front==maxn) front=0;
		for(int i=Adj[u];~i;i=edge[i].next)
		{
			int v=edge[i].to;
			if(dep[v]!=-1) continue;
			que[rear++]=v;
			if(rear==maxn) rear=0;
			dep[v]=dep[u]+1;
			++gap[dep[v]];
		}
	}
}

int SAP(int start,int end)
{
	int res=0;
	BFS(start,end);
	int cur[maxn],S[maxn];
	int top=0,i,u=start;
	memcpy(cur,Adj,sizeof(Adj));

	while(dep[start]<N)
	{
		if(u==end)
		{
			int temp=INF;
			int inser;
			for(int i=0;i<top;i++)
			{
				if(temp>edge[S[i]].cap)
				{
					temp=edge[S[i]].cap;
					inser=i;
				}
			}
			for(int i=0;i<top;i++)
			{
				edge[S[i]].cap-=temp;
				edge[S[i]^1].cap+=temp;
			}
			res+=temp;
			top=inser;
			u=edge[S[top]].from;
		}
		if(u!=end&&gap[dep[u]-1]==0) break;
		for(i=cur[u];~i;i=edge[i].next)
		{
			if(edge[i].cap!=0&&dep[u]==dep[edge[i].to]+1)
				break;
		}
		if(i!=-1)
		{
			cur[u]=i; S[top++]=i; u=edge[i].to;
		}
		else
		{
			int min=N;
			for(i=Adj[u];~i;i=edge[i].next)
			{
				if(edge[i].cap==0) continue;
				if(min>dep[edge[i].to])
				{
					min=dep[edge[i].to];
					cur[u]=i;
				}
			}
			--gap[dep[u]];
			dep[u]=min+1;
			++gap[dep[u]];
			if(u!=start)
				u=edge[S[--top]].from;
		}
	}
	return res;
}

