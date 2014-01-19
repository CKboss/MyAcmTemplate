/*
简单但是复杂度非常高的最短路O(n^3)
k--->i--->j
*/

void floyd()
{
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]));
            }
        }
    }
}
