/*
2维 RMQ (横向分裂 或 纵向分裂）
*/


int dp[10][10][310][310],mp[310][310],n,m;

void RMQ_2D_init()
{
    int mx=floor(log(n+0.0)/log(2.0));
    int my=floor(log(m+0.0)/log(2.0));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            dp[0][0][i][j]=mp[i][j];

    for(int i=0;i<=mx;i++)
    {
        for(int j=0;j<=my;j++)
        {
            if(i==0&&j==0) continue;
            for(int row=1;row+(1<<i)-1<=n;row++)
            {
                for(int col=1;col+(1<<j)-1<=m;col++)
                {
                    if(i==0)
                        dp[i][j][row][col]=max(dp[i][j-1][row][col],dp[i][j-1][row][col+(1<<(j-1))]);
                    else
                        dp[i][j][row][col]=max(dp[i-1][j][row][col],dp[i-1][j][row+(1<<(i-1))][col]);
                }
            }
        }
    }
}

int RMQ_2D(int x1,int y1,int x2,int y2)
{
    int mx=floor(log(x2-x1+1.0)/log(2.0));
    int my=floor(log(y2-y1+1.0)/log(2.0));

    int m1=dp[mx][my][x1][y1];
    int m2=dp[mx][my][x2-(1<<mx)+1][y2-(1<<my)+1];
    int m3=dp[mx][my][x1][y2-(1<<my)+1];
    int m4=dp[mx][my][x2-(1<<mx)+1][y1];

    return max(max(m1,m2),max(m3,m4));
}

