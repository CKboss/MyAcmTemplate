
/// Miller_Rabin  判断大数(2^63)是否是素数
  
typedef long long int LL;  
  
const int S=8;///判断几次 (8~12)  
  
/// (a*b)%c  
LL mult_mod(LL a,LL b,LL c)  
{  
    a%=c; b%=c;  
    LL ret=0; LL temp=a;  
    while(b)  
    {  
        if(b&1)  
        {  
            ret+=temp;  
            if(ret>c) ret-=c;  
        }  
        temp<<=1;  
        if(temp>c) temp-=c;  
        b>>=1LL;  
    }  
    return ret;  
}  
  
/// (a^n)%mod  
LL pow_mod(LL a,LL n,LL mod)  
{  
    LL ret=1;  
    LL temp=a%mod;  
    while(n)  
    {  
        if(n&1) ret=mult_mod(ret,temp,mod);  
        temp=mult_mod(temp,temp,mod);  
        n>>=1LL;  
    }  
    return ret;  
}  
  
/// check a^(n-1)==1(mod n)  
bool check(LL a,LL n,LL x,LL t)  
{  
    LL ret=pow_mod(a,x,n);  
    LL last=ret;  
    for(int i=1;i<=t;i++)  
    {  
        ret=mult_mod(ret,ret,n);  
        if(ret==1&&last!=1&&last!=n-1) return true;  
        last=ret;  
    }  
    if(ret!=1) return true;  
    return false;  
}  
  
bool Miller_Rabin(LL n)  
{  
    if(n<2) return false;  
    if(n==2) return true;  
    if((n&1)==0) return false;  
    LL x=n-1;  
    LL t=0;  
    while((x&1)==0) { x>>=1; t++;}  
    srand(time(NULL));  
  
    for(int i=0;i<S;i++)  
    {  
        LL a=rand()%(n-1)+1;  
        if(check(a,n,x,t)) return false;  
    }  
    return true;  
}  
  
