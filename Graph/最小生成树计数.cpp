
最小生成树计数

/* ***********************************************
Author        :CKboss
Created Time  :2015年09月06日 星期日 09时19分54秒
File Name     :HDOJ4408.cpp
************************************************ */
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include <set>
#include <map>
 
using namespace std;
 
typedef long long int LL;
const int maxn=111;
 
int n,m,mod;
 
struct Edge
{
    int u,v,c;
    bool operator<(const Edge& edge) const
    {
        return c<edge.c;
    }
}edge[maxn*10];
 
bool vis[maxn];
int fa[maxn],ka[maxn];
LL C[maxn][maxn],G[maxn][maxn];
vector<int> geo[maxn];
 
int find(int x,int* fa)
{
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x],fa);
}
 
LL det(LL a[][maxn],int n)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            a[i][j]%=mod;
    LL ret=1;
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            while(a[j][i])
            {
                LL t=a[i][i]/a[j][i];
                for(int k=i;k<n;k++)
                {
                    a[i][k]=(a[i][k]-a[j][k]*t)%mod;
                }
                for(int k=i;k<n;k++)
                {
                    swap(a[i][k],a[j][k]);
                }
                ret=-ret;
            }
        }
        if(a[i][i]==0) return 0;
        ret=ret*a[i][i]%mod;
    }
    return (ret+mod)%mod;
}
 
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
 
    while(scanf("%d%d%d",&n,&m,&mod)!=EOF)
    {
        if(n==0&&m==0&&mod==0) break;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].c);
        }
        sort(edge,edge+m);
        for(int i=1;i<=n;i++) fa[i]=ka[i]=i;
        memset(C,0,sizeof(C));
        int prelen=edge[0].c;
        LL ans=1;
        for(int i=0;i<=m;i++)
        {
            if((edge[i].c!=prelen)||(i==m))
            {
 
                // state over
 
                for(int j=1;j<=n;j++)
                {
                    if(vis[j])
                    {
                        geo[find(j,ka)].push_back(j);
                        vis[j]=false;
                    }
                }
 
                for(int j=1;j<=n;j++)
                {
                    int sz=geo[j].size();
                    if(sz>1)
                    {
                        memset(G,0,sizeof(G));
                        for(int a=0;a<sz;a++)
                        {
                            for(int b=a+1;b<sz;b++)
                            {
                                int u=geo[j][a],v=geo[j][b];
                                G[a][b]=(G[b][a]-=C[u][v]);
                                G[a][a]+=C[u][v]; G[b][b]+=C[u][v];
                            }
                        }
                        LL ret=det(G,sz);
                        ans=(ans*ret)%mod;
                        for(int a=0;a<sz;a++) fa[geo[j][a]]=j;
                    }
                }
 
                for(int j=1;j<=n;j++)
                {
                    ka[j]=fa[j]=find(j,fa);
                    geo[j].clear();
                }
 
                if(i==m) break;
                prelen=edge[i].c; i--;
            }
            else
            {
                int u=find(edge[i].u,fa);
                int v=find(edge[i].v,fa);
                if(u==v) continue;
                vis[u]=vis[v]=true;
                ka[find(u,ka)]=find(v,ka);
                C[u][v]++; C[v][u]++;
            }
        }
        bool flag=true;
        for(int i=2;i<=n&&flag;i++)
            if(ka[i]!=ka[i-1]) flag=false;
        if(m==0) flag=false;
        if(flag==false) ans=0;
        printf("%lld\n",ans);
    }
 
    return 0;
}

