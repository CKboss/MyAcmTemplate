
// dp[i][j]从i点到j点去掉边ij可以得到次小边

double dp[maxn][maxn];

double dfs(int P,int u,int fa,int deep)
{
    double ret=inf;
    if(deep!=1) ret=G[u][P];

    for(int i=Adj[u];~i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v==fa) continue;

        double tt=dfs(P,v,u,deep+1);
        ret=min(ret,tt);

        dp[u][v]=dp[v][u]=min(dp[u][v],tt);
    }

    return ret;
}


for(int i=0;i<n;i++)
  dfs(i,i,-1,0);
