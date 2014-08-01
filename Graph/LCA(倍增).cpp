/*LCA倍增法,在线的LCA*/

int fa[maxn][DEG];///fa[i][j]i号节点的第2^j的祖先
int deg[maxn];///深度

void BFS(int root)
{
	queue<int> q;	
	deg[root]=0;
	fa[root][0]=root;
	q.push(root);
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		for(int i=1;i<DEG;i++)
		{
			fa[u][i]=fa[fa[u][i-1]][i-1];
		}
		for(int i=Adj[u];~i;i=edge[i].next)
		{
			int v=edge[i].to;
			if(v==fa[u][0]) continue;
			deg[v]=deg[u]+1;
			fa[v][0]=u;
			q.push(v);
		}
	}
}

int LCA(int u,int v)
{
	if(deg[u]>deg[v]) swap(u,v);
	int hu=deg[u],hv=deg[v];
	int tu=u,tv=v;
	for(int det=hv-hu,i=0;det;i++,det=det/2)	
		if(det&1)
			tv=fa[tv][i];
	if(tu==tv) return tu;
	for(int i=DEG-1;i>=0;i--)
	{
		if(fa[tu][i]==fa[tv][i])
			continue;
		tu=fa[tu][i];
		tv=fa[tv][i];
	}
	return fa[tu][0];
}

