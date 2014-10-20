/*
  DLX重复覆盖 FZU686
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn=250,maxm=250;
const int maxnode=maxn*maxm;
const int INF=0x3f3f3f3f;

int n,m;
int GA[20][20];

struct DLX
{
    int n,m,size;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[maxnode],S[maxnode];
    bool vis[maxm];
    int ansd;

    void init(int _n,int _m)
    {
        ansd=INF;
        n=_n; m=_m;
        for(int i=0;i<=m;i++)
        {
            S[i]=0; U[i]=D[i]=i;
            L[i]=i-1; R[i]=i+1;
        }
        R[m]=0; L[0]=m;
        size=m;
        for(int i=1;i<=n;i++)
        {
            H[i]=-1;
        }
    }

    void Link(int r,int c)
    {
        //cout<<"Link: "<<r<<","<<c<<endl;
        ++S[Col[++size]=c];
        Row[size]=r;
        D[size]=D[c];
        U[D[c]]=size;
        U[size]=c;
        D[c]=size;
        if(H[r]<0) H[r]=L[size]=R[size]=size;
        else
        {
            R[size]=R[H[r]];
            L[R[H[r]]]=size;
            L[size]=H[r];
            R[H[r]]=size;
        }
    }
    void remove(int c)
    {
        for(int i=D[c];i!=c;i=D[i])
            L[R[i]]=L[i],R[L[i]]=R[i];
    }
    void resume(int c)
    {
        for(int i=U[c];i!=c;i=U[i])
            L[R[i]]=R[L[i]]=i;
    }
    int Astart()
    {
        int ret=0;
        for(int i=R[0];i!=0;i=R[i]) vis[i]=true;
        for(int c=R[0];c!=0;c=R[c])
        {
            if(vis[c]==true)
            {
                ret++;
                vis[c]=false;
                for(int i=D[c];i!=c;i=D[i])
                    for(int j=R[i];j!=i;j=R[j])
                        vis[Col[j]]=false;
            }
        }
        return ret;
    }
    void Dance(int d)
    {
        if(d+Astart()>=ansd) return ;
        if(R[0]==0)
        {
            ///find ans;
            ansd=min(ansd,d);
            return ;
        }
        int c=R[0];
        for(int i=R[0];i!=0;i=R[i])
            if(S[i]<S[c]) c=i;
        for(int i=D[c];i!=c;i=D[i])
        {
            remove(i);
            for(int j=R[i];j!=i;j=R[j]) remove(j);
            Dance(d+1);
            for(int j=L[i];j!=i;j=L[j]) resume(j);
            resume(i);
        }
    }
};

DLX dlx;

int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        int gn=1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                scanf("%d",&GA[i][j]);
                if(GA[i][j]==1) GA[i][j]=gn++;
            }
        int n1,m1;
        scanf("%d%d",&n1,&m1);
        ///attract point
        int ap=(n-n1+1)*(m-m1+1);
        gn--;
        dlx.init(ap,gn);
        for(int i=1;i+n1-1<=n;i++)
        {
            for(int j=1;j+m1-1<=m;j++)
            {
                int nap=(i-1)*(m-m1+1)+j;
                for(int ii=i;ii<=i+n1-1;ii++)
                {
                    for(int jj=j;jj<=j+m1-1;jj++)
                    {
                        if(GA[ii][jj])
                            dlx.Link(nap,GA[ii][jj]);
                    }
                }
            }
        }
        dlx.Dance(0);
        printf("%d\n",dlx.ansd);
    }
    return 0;
}
