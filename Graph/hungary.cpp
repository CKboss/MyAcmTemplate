
//匈牙利二分图匹配dfs
/**************hungary************/

int linker[maxn];
bool used[maxn];

bool dfs(int u)
{
    for(int i=Adj[u];~i;i=edge[i].next)
    {
        int v=edge[i].to;
        if(!used[v])
        {
            used[v]=true;
            if(linker[v]==-1||dfs(linker[v]))
            {
                linker[v]=u;
                return true;
            }
        }
    }
    return false;
}

int hungary()
{
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(int u=0;u<n;u++)
    {
        memset(used,false,sizeof(used));
        if(dfs(u)) res++;
    }
    return res;
}
