/* trajian LCA 
  dfs+并查集 离线处理最近公共祖先
*/

void LCA(int u,int father)  
{  
    for(int i=Adj[u];~i;i=edge[i].next)  
    {  
        int v=edge[i].to;  
        if(v==father) continue;  
        Distan[v]=Distan[u]+edge[i].distan;  
        LCA(v,u);  
        fa[v]=u;          
    }  
    vis[u]=true;  
    for(int i=Adj2[u];~i;i=edge2[i].next)  //每一询问加两条边
    {  
        int v=edge2[i].to;  
        int id=edge2[i].distan;  
        if(vis[v])    
        {  
            ans[id]=Distan[u]+Distan[v]-2*Distan[Find(v)];  
            //LCA即 Find(v)
        }  
    }  
}  
