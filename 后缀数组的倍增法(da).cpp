#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 2e5 + 5;

int sa[N],rank[N],rank2[N],height[N],cnt[N],*x,*y;

/*
    * a radix_sort which is based on the y[].
    * how ? ahhhh, the last reverse for is the solution.
    * and the adjacant value of sa[] might have the same rank.
*/
void radix_sort(int n,int sz)
{
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<n;i++)
        cnt[ x[ y[i] ] ]++;
    for(int i=1;i<sz;i++)
        cnt[i] += cnt[i-1];
    for(int i=n-1;i>=0;i--)
        sa[ --cnt[ x[ y[i] ] ] ] = y[i];
}

/*
    * sa[i] represents the ith suffix string is which one.
    * rank[i] represents the suffix string [i,n]'s rank.
    * sz is the max_rank of text in that time.
    * x[] represents the true pointer of rank[] in that time and it may be not unique.
    * y[] is the location of text[] which is sorted by 2nd key in that time before swap(x,y).
*/
void get_sa(char text[],int n,int sz=128)
{
    x = rank, y = rank2;
    for(int i=0;i<n;i++)
        x[i] = text[i], y[i] = i;
    radix_sort(n,sz);
    for(int len=1;len<n;len<<=1)
    {
        int yid = 0;
        for(int i=n-len;i<n;i++)
            y[yid++] = i;
        for(int i=0;i<n;i++)
            if(sa[i] >= len)
                y[yid++] = sa[i] - len;
        radix_sort(n,sz);
        swap(x,y);
        x[ sa[0] ] = yid = 0;
        for(int i=1;i<n;i++)
        {
            if(y[ sa[i-1] ]==y[ sa[i] ] && sa[i-1]+len<n && sa[i]+len<n && y[ sa[i-1]+len ]==y[ sa[i]+len ])
                x[ sa[i] ] = yid;
            else
                x[ sa[i] ] = ++yid;
        }
        sz = yid + 1;
        if(sz >= n)
            break;
    }
    for(int i=0;i<n;i++)
        rank[i] = x[i];
}

/*
    * height[] represents the longest common prefix of suffix [i-1,n] and [i,n].
    * height[ rank[i] ] >= height[ rank[i-1] ] - 1.
    ..... let's call [k,n] is the suffix which rank[k] = rank[i-1] - 1,
    ...=> [k+1,n] is a suffix which rank[k+1] < rank[i]
    ..... and the lcp of [k+1,n] and [i,n] is height[ rank[i] ] - 1.
    ..... still unknow ? height[ rank[i] ] is the max lcp of rank[k] and rank[i] which rank[k] < rank[i].
*/
void get_height(char text[],int n)
{
    int k = 0;
    for(int i=0;i<n;i++)
    {
        if(rank[i] == 0)
            continue;
        k = max(0,k-1);
        int j = sa[ rank[i]-1 ];
        while(i+k<n && j+k<n && text[i+k]==text[j+k])
            k++;
        height[ rank[i] ] = k;
    }
}

namespace RMQ
{
    int dp[20][N];
    void init(int c[],int n)
    {
        for(int i=0;i<n;i++)
            dp[0][i] = c[i];
        for(int j=1;j<20;j++)
            for(int i=0;i+(1<<j)-1<n;i++)
                dp[j][i] = min(dp[j-1][i],dp[j-1][i+(1<<(j-1))]);
    }
    int _log2(int n)
    {
        int ret = 0;
        while(1<<(ret+1) <= n)
            ret++;
        return ret;
    }
    int get_min(int a,int b)
    {
        int k = _log2(b-a+1);
        return min(dp[k][a],dp[k][b-(1<<k)+1]);
    }
}

int lcp(int a,int b)
{
    a = rank[a] , b = rank[b];
    if(a > b)   swap(a,b);
    return RMQ::get_min(a+1,b);
}
