/*高斯消元浮点数版 n^3 */

const double eps=1e-9;
const int maxn=550;

double a[maxn][maxn],x[maxn]; //a等式左边的矩阵 x矩阵右边的的值 x求解后即储存结果
int equ,val; //等式数 变量数

bool Gauss()
{
    int i,j,k,col,max_r;
    for(k=0,col=0;k<equ&&col<val;k++,col++)
    {
        max_r=k;
        for(i=k+1;i<equ;i++)
            if(fabs(a[i][col])>fabs(a[max_r][col]))
                max_r=i;
        if(fabs(a[max_r][col]<eps))
            return false;
        if(k!=max_r)
        {
            for(j=col;j<val;j++)
                swap(a[k][j],a[max_r][j]);
            swap(x[k],x[max_r]);
        }
        x[k]/=a[k][col];
        for(j=col+1;j<val;j++)
            a[k][j]/=a[k][col];
        a[k][col]=1;
        for(int i=0;i<equ;i++)
        {
            if(i!=k)
            {
                x[i]-=x[k]*a[i][k];
                for(j=col+1;j<val;j++)
                    a[i][j]-=a[k][j]*a[i][col];
                a[i][col]=0;
            }
        }
    }
    return true;
}
