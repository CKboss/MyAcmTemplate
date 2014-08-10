///lucas(n,m,p)=c[n%p][m%p]*lucas(n/p,m/p,p);  组合数取模 p<10^5

LL fact[100100];  
  
LL QuickPow(LL x,LL t,LL m)  
{  
    if(t==0) return 1LL;  
    LL e=x,ret=1LL;  
    while(t)  
    {  
        if(t&1) ret=(ret*e)%m;  
        e=(e*e)%m;  
        t>>=1LL;  
    }  
    return ret%m;  
}  
  
void get_fact(LL p)  
{  
    fact[0]=1LL;  
    for(int i=1;i<=p+10;i++)  
        fact[i]=(fact[i-1]*i)%p;  
}  
  
LL Lucas(LL n,LL m,LL p)  
{  
    ///lucas(n,m,p)=c[n%p][m%p]*lucas(n/p,m/p,p);  
    LL ret=1LL;  
    while(n&&m)  
    {  
        LL a=n%p,b=m%p;  
        if(a<b) return 0;  
        ret=(ret*fact[a]*QuickPow((fact[b]*fact[a-b])%p,p-2,p))%p;  
        n/=p; m/=p;  
    }  
    return ret%p;  
}  
  

