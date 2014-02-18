

int TU[400];

int dp[400][10];

int RMQ_init()
{
    for(int i=1;i<=m;i++) dp[i][0]=TU[i];

    for(int j=1;(1<<j)<=m;j++)
    {
        for(int i=1;i+(1<<j)-1<=m;i++)
        {
            dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
        }
    }
}

int RMQ(int L,int R)
{
    int k;
    while((1<<(k+1))<=(R-L+1)) k++;
    //k=floor(log(R-L+1.0)/log(2.0));
    return max(dp[L][k],dp[R-(1<<k)+1][k]);
}
