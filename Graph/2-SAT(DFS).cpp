/*
dfs 写法简单易懂,可以方便的输出字典序最小的解
*/
bool vis[maxn];
int top,S[maxn];

bool dfs(int x)
{
    if(vis[x^1]) return false;
    if(vis[x]) return true;
    S[top++]=x; vis[x]=true;
    for(int i=Adj[x];~i;i=edge[i].next)
    {
        if(!dfs(edge[i].to)) return false;
    }
    return true;
}

bool SAT2(int n)
{
    memset(vis,false,sizeof(vis));
    for(int i=0;i<n;i+=2)
    {
        if(vis[i]||vis[i^1]) continue;
        top=0;
        if(!dfs(i))
        {
            while(top) vis[S[--top]]=false;
            if(!dfs(i^1)) return false;
        }
    }
    return true;
}
