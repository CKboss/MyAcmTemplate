
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

