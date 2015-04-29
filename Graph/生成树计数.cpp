/*
Matrix-Tree 定理(Kirchhoff 矩阵-树定理)
1、G 的度数矩阵 D[G]是一个 n*n 的矩阵,并且满足:当 i≠j 时,dij=0;当 i=j 时,dij 等于 vi 的度数。
2、G 的邻接矩阵 A[G]也是一个 n*n 的矩阵, 并且满足:如果 vi、vj 之间有边直接相连,则 aij=1,否则
为 0。
我们定义 G 的 Kirchhoff 矩阵(也称为拉普拉斯算子)C[G]为 C[G]=D[G]-A[G],则 Matrix-Tree 定理可以
描述为: G 的所有不同的生成树的个数等于其 Kirchhoff 矩阵 C[G]任何一个 n-1 阶主子式的行列式的绝对
值。所谓 n-1 阶主子式,就是对于 r(1≤r≤n),将 C[G]的第 r 行、第 r 列同时去掉后得到的新矩阵,用 Cr[G]
表示。
*/

/// LD版

typedef long double LD;  
  
const LD eps=1e-10;  
  
const int maxn=60;  
  
int sgn(LD x)  
{  
    if(fabs(x)<eps) return 0; if(x<0) return -1; return 1;  
}  
  
LD b[maxn][maxn];  
  
LD det(LD a[][maxn],int n)  
{  
    int sign=0;  
    int i,j,k;  
    LD ret=1;  
    for(i=0;i<n;i++)  
        for(j=0;j<n;j++)  
            b[i][j]=a[i][j];  
    for(i=0;i<n;i++)  
    {  
        if(sgn(b[i][i])==0)  
        {  
            for(j=i+1;j<n;j++)  
                if(sgn(b[j][i])!=0)  
                    break;  
            if(j==n) return 0;  
            for(k=i;k<n;k++)  
                swap(b[i][k],b[j][k]);  
            sign++;  
        }  
        ret*=b[i][i];  
        for(k=i+1;k<n;k++)  
            b[i][k]/=b[i][i];  
        for(j=i+1;j<n;j++)  
            for(k=i+1;k<n;k++)  
                b[j][k]-=b[j][i]*b[i][k];  
    }  
    if(sign&1) ret=-ret;  
    return ret;  
}  

/// 取mod版

LL inv(LL a,LL m)  
{  
    if(a==1) return 1;  
    return inv(m%a,m)*(m-m/a)%m;  
}  
  
LL det(LL a[][maxn],int n)  
{  
    for(int i=0;i<n;i++)  
        for(int j=0;j<n;j++)  
            b[i][j]=(a[i][j]+MOD)%MOD;  
    int res=1;  
    for(int i=0;i<n;i++)  
    {  
        for(int j=i;j<n;j++)  
        {  
            if(b[j][i]!=0)  
            {  
                for(int k=i;k<n;k++)  
                    swap(b[i][k],b[j][k]);  
                if(i!=j)  
                    res=(MOD-res)%MOD;  
                break;  
            }  
        }  
        if(b[i][i]==0)  
        {  
            res=-1; break;  
        }  
        for(int j=i+1;j<n;j++)  
        {  
            LL mut=(b[j][i]*inv(b[i][i],MOD))%MOD;  
            for(int k=i;k<n;k++)  
                b[j][k]=(b[j][k]-(b[i][k]*mut)%MOD+MOD)%MOD;  
        }  
        res=(res*b[i][i])%MOD;  
    }  
    return res;  
}  
  
