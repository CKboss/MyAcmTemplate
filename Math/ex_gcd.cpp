
/* a*x + b*y = gcd(a,b)
中 abs(x)+abs(y) 最小的解
*/

void ex_gcd(LL a,LL b,LL &d,LL &x,LL &y)
{
	if(!b)
	{
		d=a; x=1; y=0;
	}
	else
	{
		ex_gcd(b,a%b,d,y,x);
		y-=a/b*x;
	}	
}

/* a和n的乘法逆元 */

LL inv(int a,int n)
{
  LL d,x,y;
  ex_gcd(a,n,d,x,y);
  if(d!=1) retunrn -1;
  else return (x%mod+mod)%mod;
}

/* 预处逆元 及 组合数的模 */

LL inv[maxn];  
LL jc[maxn],jcv[maxn];  // 阶乘 阶乘逆
  
void init()  
{  
    /// inv jc
    inv[1]=1; jc[0]=1; jcv[0]=1;   
    jc[1]=1; jcv[1]=1;
    for(int i=2;i<maxn;i++)  
    {  
        inv[i]=inv[mod%i]*(mod-mod/i)%mod;  
        jc[i]=(jc[i-1]*i)%mod;  
        jcv[i]=(jcv[i-1]*inv[i])%mod;  
    }  
}  
  
LL COMB(LL n,LL m)  
{  
    if(m<0||m>n) return 0LL;  
    if(m==0||m==n) return 1LL;  
    /// n!/((n-m)!*m!)  
    LL ret=((jc[n]*jcv[n-m])%mod*jcv[m])%mod;  
    return ret;  
}  

