/*
kruscal最小生成树，比prim慢
*/

struct Edge
{
    int u,v,w;
}edge[220000];

int getfa(int x)
{
    if(x==fa[x]) return x;
    else return fa[x]=getfa(fa[x]);
}

int kruscal()
{
    sort(edge,edge+m,cmp);
    int cnt=n,ans=0;
    for(int i=0;i<n;i++) fa[i]=i;
    for(int i=0;i<m;i++)
    {
        int f1=getfa(edge[i].u);
        int f2=getfa(edge[i].v);

        if(f1!=f2)
        {
            fa[f1]=f2;
            ans+=edge[i].w;
            cnt--;
            if(cnt==1) break;
        }
    }
    return (cnt==1)?ans:0x3f3f3f3f;
}
