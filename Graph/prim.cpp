/*
prim 在稠密图上效果更好的MST
*/
int dist[2200];
bool vis[2200];
int prim()
{
    memset(dist,63,sizeof(dist));
    memset(vis,0,sizeof(vis));

    dist[0]=0;

    int sum=0;
    for(int i=0;i<n;i++)
    {
        int mark=-1,mindis=0x3f3f3f3f;

        for(int j=0;j<n;j++)
        {
            if(!vis[j]&&dist[j]<mindis)
            {
                mindis=dist[j];
                mark=j;
            }
        }

        if(mark==-1) return 0x3f3f3f3f;

        sum+=mindis; vis[mark]=true;

        for(int j=0;j<n;j++)
        {
            if(!vis[j]&&g[mark][j]<dist[j])
            {
                dist[j]=g[mark][j];
            }
        }
    }

    return sum;
}
