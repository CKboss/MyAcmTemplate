/*
小于n且与n互素的整数的个数
*/

int euler_phi(int n)
{
    int ans=n;
    for(int i=2;i*i<=n;i++)
        if(n%i==0)
        {
            ans=ans/i*(i-1);
            while(n%i==0) n/=i;
        }
    if(n>1) ans=ans/n*(n-1);
    return ans;
}

int phi[110];

void phi_table(int n,int* phi)
{
    memset(phi,0,sizeof(phi));
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!phi[i])
        {
            for(int j=i;j<=n;j+=i)
            {
                if(!phi[j]) phi[j]=j;
                phi[j]=phi[j]/i*(i-1);
            }
        }
    }
}

