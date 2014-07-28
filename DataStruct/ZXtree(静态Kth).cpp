/* POJ 2104 主席树静态区间第K大 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn=110000;

int n,m,q;
int a[maxn],t[maxn];
int T[maxn],lson[maxn*50],rson[maxn*50],c[maxn*50],tot;

void init_hash()
{
	tot=0;
	sort(t+1,t+1+n);
	m=unique(t+1,t+1+n)-t;
}

int hash(int x)
{
	return lower_bound(t+1,t+1+n,x)-t;
}

int build(int l,int r)
{
	int root=tot++,temp=root;
	c[root]=0;
	if(l!=r)
	{
		int mid=(l+r)/2;
		lson[root]=build(l,mid);
		rson[root]=build(mid+1,r);
	}
	return temp;
}

int update(int root,int pos,int val)
{
	int newroot=tot++,temp=newroot;
	c[newroot]=c[root]+val;
	int l=1,r=m;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(pos<=mid)
		{
			r=mid;
			lson[newroot]=tot++;
			rson[newroot]=rson[root];
			root=lson[root];
			newroot=lson[newroot];
		}
		else
		{
			l=mid+1;
			rson[newroot]=tot++;
			lson[newroot]=lson[root];
			root=rson[root];
			newroot=rson[newroot];
		}
		c[newroot]=c[root]+val;
	}
	return temp;	
}

int query(int left_son,int right_son,int x)
{
	int l=1,r=m;
	while(l<r)	
	{
		int mid=(l+r)/2;
		int tk=c[lson[left_son]]-c[lson[right_son]];
		if(tk>=x)
		{
			left_son=lson[left_son];
			right_son=lson[right_son];
			r=mid;
		}
		else
		{
			l=mid+1;
			x-=tk;
			left_son=rson[left_son];
			right_son=rson[right_son];
		}
	}
	return l;
}

int main()
{
	while(scanf("%d%d",&n,&q)!=EOF)
	{
		for(int i=1;i<=n;i++)
		{
			scanf("%d",a+i);
			t[i]=a[i];
		}
		init_hash();
		T[n+1]=build(1,m);
		for(int i=n;i;i--)
		{
			T[i]=update(T[i+1],hash(a[i]),1);
		}
		while(q--)
		{
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			printf("%d\n",t[query(T[a],T[b+1],c)]);
		}
	}
	return 0;
}


