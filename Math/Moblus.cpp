
bool check[maxn];  
int prime[maxn],mu[maxn];  
  
void Moblus()  
{  
    memset(check,true,sizeof(check));  
    mu[1]=1;  
    int tot=0;  
    for(int i=2;i<maxn;i++)  
    {  
        if(check[i])  
        {  
            prime[tot++]=i; mu[i]=-1;  
        }  
        for(int j=0;j<tot;j++)  
        {  
            int ij=prime[j]*i;  
            if(ij>maxn) break;  
            check[ij]=false;  
            if(i%prime[j]==0)  
            {  
                mu[ij]=0; break;  
            }  
            else mu[ij]=-mu[i];  
        }  
    }  
}  
