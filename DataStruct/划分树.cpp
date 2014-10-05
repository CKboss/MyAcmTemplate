/*
静态区间第K大的简单方法
*/

const int maxn=100100;

int tree[20][maxn];///第i层的排列情况
int sorted[maxn];///排好序的数组
int toleft[20][maxn];///第i层从1.到..j移动到左边的数的个数

void build(int l,int r,int dep)
{
    if(l==r) return ;
    int mid=(l+r)/2;
    int same=mid-l+1;///与mid相同的但要移动到左边的数的个数
    for(int i=l;i<=r;i++)
        if(tree[dep][i]<sorted[mid]) same--;
    int lpos=l,rpos=mid+1;
    for(int i=l;i<=r;i++)
    {
        if(tree[dep][i]<sorted[mid])
            tree[dep+1][lpos++]=tree[dep][i];
        else if(tree[dep][i]==sorted[mid]&&same>0)
        {
            tree[dep+1][lpos++]=tree[dep][i];
            same--;
        }
        else tree[dep+1][rpos++]=tree[dep][i];

        toleft[dep][i]=toleft[dep][l-1]+lpos-l;
    }
    build(l,mid,dep+1);
    build(mid+1,r,dep+1);
}


int query(int L,int R,int l,int r,int dep,int k)
{
    if(l==r) return tree[dep][l];
    int mid=(L+R)/2;
    int cnt=toleft[dep][r]-toleft[dep][l-1];
    if(cnt>=k)
    {
        int newl=L+toleft[dep][l-1]-toleft[dep][L-1];
        int newr=newl+cnt-1;
        return query(L,mid,newl,newr,dep+1,k);
    }
    else
    {
        int newr=r+toleft[dep][R]-toleft[dep][r];
        int newl=newr-(r-l-cnt);
        return query(mid+1,R,newl,newr,dep+1,k-cnt);
    }
}

int main()
{
    int T_T,n,m;
    scanf("%d",&T_T);
    while(T_T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",sorted+i);
            tree[0][i]=sorted[i];
        }
        sort(sorted+1,sorted+1+n);
        build(1,n,0);
        int l,r,k;
        while(m--)
        {
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",query(1,n,l,r,0,k));
        }
    }
    return 0;
}
