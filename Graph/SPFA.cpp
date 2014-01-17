/*
bellman_fold 的队列优化版
*/

int dist[MaxV],cQ[MaxV];
bool inQ[MaxV];

bool spfa()
{
    memset(dist,63,sizeof(dist));
    memset(cQ,0,sizeof(cQ));
    memset(inQ,false,sizeof(inQ));
    dist[1]=0;
    queue<int> q;
    inQ[1]=true;q.push(1); cQ[1]=1;

    while(!q.empty())
    {
        int u=q.front();q.pop();

        for(int i=Adj[u];~i;i=edge[i].next)
        {
            int v=edge[i].to;
            if(dist[v]>dist[u]+edge[i].cost)
            {
                dist[v]=dist[u]+edge[i].cost;
                if(!inQ[v])
                {
                    inQ[v]=true;
                    cQ[v]++;
                    if(cQ[v]>=MaxV) return false;
                    q.push(v);
                }
            }
        }
        inQ[u]=false;
    }
    return true;
}
