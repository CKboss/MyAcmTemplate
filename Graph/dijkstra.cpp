/*
o(v^2)的最短路
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int INF=0x3f3f3f3f;
const int maxn=1200;

int dist[maxn],g[maxn][maxn],N;
bool vis[maxn];

void dijkstra()
{
    for(int i=1;i<=N;i++)
        dist[i]=(i==1)?0:INF;
    memset(vis,0,sizeof(vis));

    for(int i=1;i<=N;i++)
    {
        int mark=-1,mindis=INF;
        for(int j=1;j<=N;j++)
        {
            if(!vis[j]&&dist[j]<mindis)
            {
                mindis=dist[j];
                mark=j;
            }
        }
        vis[mark]=1;

        for(int j=1;j<=N;j++)
        {
            if(!vis[j])
            {
                dist[j]=min(dist[j],dist[mark]+g[mark][j]);
            }
        }
    }
}

int main()
{
    return 0;
}

// 堆优化dijkstra

void dijkstra()
{
	memset(dist,63,sizeof(dist));
	dist[S]=0;
	priority_queue<pII> q; /// -距离,点
	q.push(make_pair(0,S));

	while(!q.empty())
	{
		pII tp=q.top(); q.pop();
		LL u=tp.second;
		if(vis[u]==true) continue;
		vis[u]=true;
		for(LL i=Adj[u];~i;i=edge[i].next)
		{
			LL v=edge[i].to;
			LL len=edge[i].len;
			if(vis[v]) continue;
			if(dist[v]>dist[u]+len)
			{
				dist[v]=dist[u]+len;
				q.push(make_pair(-dist[v],v));
			}
		}
	}
}
