#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <cmath>  
#include <set>  
#include <algorithm>  
  
using namespace std;  
  
const int maxn=1000012;  
  
int sa[maxn],rank[maxn],rank2[maxn],h[maxn],c[maxn],*x,*y,ans[maxn];  
char str[maxn];  
  
bool cmp(int* r,int a,int b,int l,int n)  
{  
    if(r[a]==r[b]&&a+l<n&&b+l<n&&r[a+l]==r[b+l]) return true;  
    return false;  
}  
  
void radix_sort(int n,int sz)  
{  
    for(int i=0;i<sz;i++) c[i]=0;  
    for(int i=0;i<n;i++) c[x[y[i]]]++;  
    for(int i=1;i<sz;i++) c[i]+=c[i-1];  
    for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];  
}  
  
void get_sa(char c[],int n,int sz=128)  
{  
    x=rank,y=rank2;  
    for(int i=0;i<n;i++) x[i]=c[i],y[i]=i;  
    radix_sort(n,sz);  
    for(int len=1;len<n;len<<=1)  
    {  
        int yid=0;  
        for(int i=n-len;i<n;i++) y[yid++]=i;  
        for(int i=0;i<n;i++) if(sa[i]>=len) y[yid++]=sa[i]-len;  
  
        radix_sort(n,sz);  
  
        swap(x,y);  
        x[sa[0]]=yid=0;  
  
        for(int i=1;i<n;i++)  
        {  
            x[sa[i]]=cmp(y,sa[i],sa[i-1],len,n)?yid:++yid;  
        }  
  
        sz=yid+1;  
        if(sz>=n) break;  
    }  
    for(int i=0;i<n;i++) rank[i]=x[i];  
}  
  
  
void get_h(char str[],int n)  
{  
    int k=0; h[0]=0x3f3f3f3f;  
    for(int i=0;i<n;i++)  
    {  
        if(rank[i]==0) continue;  
        k=max(k-1,0);  
        int j=sa[rank[i]-1];  
        while(i+k<n&&j+k<n&&str[i+k]==str[j+k]) k++;  
        h[rank[i]]=k;  
    }  
}  
  
int dp[maxn][20],Log[maxn];  
  
void RMQ_init(int n)  
{  
    for(int i=0;i<n;i++) dp[i][0]=h[i];  
    for(int i=1;i<=Log[n];i++)  
    {  
        for(int j=0;j+(1<<i)-1<n;j++)  
        {  
            dp[j][i]=min(dp[j][i-1],dp[j+(1<<(i-1))][i-1]);  
        }  
    }  
}  
  
int lcp(int l,int r)  
{  
    l=rank[l];r=rank[r];  
    if(l>r) swap(l,r);  
    int a=l+1,b=r;  
    int k=Log[b-a+1];  
    return min(dp[a][k],dp[b-(1<<k)+1][k]);  
}  
  
int main()  
{  
    int cas=1;  
    Log[0] = -1;  
    for(int i=1;i<=maxn;i++)  
    {  
        Log[i]=(i&(i-1))?Log[i-1]:Log[i-1] + 1 ;  
    }  
    while(scanf("%s",str)!=EOF&&str[0]!='#')  
    {  
        int n=strlen(str);  
  
        get_sa(str,n);  
        get_h(str,n);  
        RMQ_init(n);  
    }
    return 0;
}
