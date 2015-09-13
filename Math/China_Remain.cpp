

********China remain ********************/

void ex_gcd(LL a,LL b,LL& d,LL &x,LL &y)
{
	if(b==0)
	{
		d=a; x=1; y=0;
	}
	else
	{
		ex_gcd(b,a%b,d,y,x);
		y-=x*(a/b);
	}
}

LL divisor[20],remain[20];

/// m: divisor a: remainder
LL china(LL n,LL* m,LL* a)
{
	LL aa=a[0];
	LL mm=m[0];
	for(int i=0;i<n;i++)
	{
		LL sub=a[i]-aa;

		LL d,x,y;
		ex_gcd(mm,m[i],d,x,y);
		if(sub%d) return -1;

		LL new_m=m[i]/d;
		new_m=(sub/d*x%new_m+new_m)%new_m;

		aa=mm*new_m+aa;
		mm=mm*m[i]/d;
	}
	aa=(aa+mm)%mm;
	return aa;
}


