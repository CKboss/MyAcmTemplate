/*分治法的最近点对*/

bool cmpxy(POINT a,POINT b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}

bool cmpy(POINT a,POINT b)
{
    return a.y<b.y;
}

inline LL square(LL x)
{
    return x*x;
}

LL dist(POINT a,POINT b)
{
    return square(a.x-b.x)+square(a.y-b.y);
}

LL Close_pair(int left,int right)
{
    LL d=INF;
    if(left==right) return INF;
    if(left+1==right) return dist(p[left],p[right]);
    int mid=(left+right)/2;
    d=min(Close_pair(left,mid),Close_pair(mid+1,right));

    int k=0;
    for(int i=left;i<=right;i++)
    {
        if(square(p[i].x-p[mid].x)<=d)
        {
            temp[k++]=p[i];
        }
    }
    sort(temp,temp+k,cmpy);
    for(int i=0;i<k;i++)
    {
        for(int j=i+1;j<k&&square(temp[i].y-temp[j].y)<d;j++)
        {
            d=min(d,dist(temp[i],temp[j]));
        }
    }
    return d;
}

