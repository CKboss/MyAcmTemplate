const int maxn=50;
int equ,var;//等式数,变量数
int a[maxn][maxn],x[maxn];//矩阵(多一列最终状态),答案
int free_x[maxn],free_num;//自由变元
int Gauss()
{
    int max_r,col,k;
    free_num=0;
    for(k=0,col=0;k<equ&&col<var;k++,col++)
    {
        max_r=k;
        for(int i=k+1;i<equ;i++)
        {
            if(abs(a[i][col])>abs(a[max_r][col]))
                max_r=i;
        }
        if(a[max_r][col]==0)
        {
            k--;
            free_x[free_num++]=col;
            continue;
        }
        if(max_r!=k)
        {
            for(int j=col;j<var+1;j++)
                swap(a[k][j],a[max_r][j]);
        }
        for(int i=k+1;i<equ;i++)
        {
            if(a[i][col]!=0)
            {
                for(int j=col;j<var+1;j++)
                    a[i][j]^=a[k][j];
            }
        }
    }
    for(int i=k;i<equ;i++)
        if(a[i][col]!=0)
            return -1;
    if(k<var) return var-k;
    for(int i=var-1;i>=0;i--)
    {
        x[i]=a[i][var];
        for(int j=i+1;j<var;j++)
            x[i]^=(a[i][j]&&x[j]);
    }
    return 0;
}
        
