/*树状数组套主席数维护动态第K大*/

/**************************************************************
    Problem: 1901
    User: CKboss
    Language: C++
    Result: Accepted
    Time:488 ms
    Memory:55480 kb
****************************************************************/
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
const int maxn=101000;
const int MAXN=2560000;
 
int n,m,tot,q;
int a[maxn],h[maxn];
int T[MAXN],c[MAXN],lson[MAXN],rson[MAXN];
 
struct Question
{
    int kind,l,r,k;
}Q[maxn];
 
void Init_hash(int k)
{
    sort(h,h+k);
    m=unique(h,h+k)-h;
}
 
int hash(int x)
{
    return lower_bound(h,h+m,x)-h;
}
 
int build(int l,int r)
{
    int root=tot++;
    if(l!=r)
    {
        int mid=(l+r)/2;
        lson[root]=build(l,mid);
        rson[root]=build(mid+1,r);
    }
    return root;
}
 
int update(int root,int pos,int val)
{
    int newroot=tot++,tmp=newroot;
    int l=0,r=m-1;
    c[newroot]=c[root]+val;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(pos<=mid)
        {
            lson[newroot]=tot++; rson[newroot]=rson[root];
            newroot=lson[newroot]; root=lson[root];
            r=mid;
        }
        else
        {
            rson[newroot]=tot++; lson[newroot]=lson[root];
            newroot=rson[newroot]; root=rson[root];
            l=mid+1;
        }
        c[newroot]=c[root]+val;
    }
    return tmp;
}
 
int use[maxn*30];
 
int lowbit(int x)
{
    return x&(-x);
}
 
void add(int x,int pos,int val)
{
    for(int i=x;i<=n;i+=lowbit(i))
        T[i]=update(T[i],pos,val);
}
 
int sum(int x)
{
    int ret=0;
    for(int i=x;i;i-=lowbit(i))
        ret+=c[lson[use[i]]];
    return ret;
}
 
int query(int left,int right,int k)
{
    int l=0,r=m-1;
    for(int i=left-1;i;i-=lowbit(i))
        use[i]=T[i];
    for(int i=right;i;i-=lowbit(i))
        use[i]=T[i];
    while(l<r)
    {
        int mid=(l+r)/2;
        int tmp=sum(right)-sum(left-1);
        if(tmp>=k)
        {
            r=mid;
            for(int i=left-1;i;i-=lowbit(i))
                use[i]=lson[use[i]];
            for(int i=right;i;i-=lowbit(i))
                use[i]=lson[use[i]];
        }
        else
        {
            l=mid+1;
            k-=tmp;
            for(int i=left-1;i;i-=lowbit(i))
                use[i]=rson[use[i]];
            for(int i=right;i;i-=lowbit(i))
                use[i]=rson[use[i]];
        }
    }
    return l;
}
 
void Init_tree()
{
    T[0]=build(0,m-1);
    for(int i=1;i<=n;i++)
        T[i]=T[0];
    for(int i=1;i<=n;i++)
        add(i,hash(a[i]),1);
}
 
int main()
{
while(scanf("%d%d",&n,&q)!=EOF)
{
    m=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        h[m++]=a[i];
    }
    for(int i=0;i<q;i++)
    {
        char str[5];
        int l,r,k;
        scanf("%s",str);
        if(str[0]=='Q')
        {
            scanf("%d%d%d",&l,&r,&k);
            Q[i]=(Question){0,l,r,k};
        }
        else
        {
            scanf("%d%d",&l,&k);
            Q[i]=(Question){1,l,0,k};
            h[m++]=k;
        }
    }
    Init_hash(m);
    Init_tree();
    for(int i=0;i<q;i++)
    {
        if(Q[i].kind==0)
        {
            printf("%d\n",h[query(Q[i].l,Q[i].r,Q[i].k)]);
        }
        else
        {
            add(Q[i].l,hash(a[Q[i].l]),-1);
            add(Q[i].l,hash(Q[i].k),1);
            a[Q[i].l]=Q[i].k;
        }
    }
}
    return 0;
}
