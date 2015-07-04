const int INF=0x3f3f3f3f;  
const int maxn=110;  
  
int n,m;  
  
struct Edge  
{  
    int u,v,cost;  
};  
  
Edge edge[maxn*maxn];  
int pre[maxn],id[maxn],vis[maxn],in[maxn];  
  
int zhuliu(int root,int n,int m,Edge edge[])  
{  
    int res=0,u,v;  
    while(true)  
    {  
        for(int i=0;i<n;i++) in[i]=INF;  
        for(int i=0;i<m;i++)  
        {  
            if(edge[i].u!=edge[i].v&&edge[i].cost<in[edge[i].v])  
            {  
                pre[edge[i].v]=edge[i].u;  
                in[edge[i].v]=edge[i].cost;  
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
            v=i;  
            while(vis[v]!=i&&id[v]==-1&&v!=root)  
            {  
                vis[v]=i; v=pre[v];  
            }  
            if(v!=root&&id[v]==-1)  
            {  
                for(int u=pre[v];u!=v;u=pre[u])  
                    id[u]=tn;  
                id[v]=tn++;  
            }  
        }  
        if(tn==0) break;  
        for(int i=0;i<n;i++)  
            if(id[i]==-1) id[i]=tn++;  
        for(int i=0;i<m;)  
        {  
            v=edge[i].v;  
            edge[i].u=id[edge[i].u];  
            edge[i].v=id[edge[i].v];  
            if(edge[i].u!=edge[i].v)  
                edge[i++].cost-=in[v];  
            else  
                swap(edge[i],edge[--m]);  
        }  
        n=tn;  
        root=id[root];  
    }  
    return res;  
}  
  
