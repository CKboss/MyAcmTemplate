/*基于排序的离散化*/
int r[maxn],md[maxn],m;
bool cmpR(int a,int b)
{
    return val[a]<val[b];
}
void Lisan()
{
    for(int i=0;i<=n;i++) r[i]=i;
    sort(r+1,r+1+n,cmpR);
    md[1]=val[r[1]];
    val[r[1]]=m=1;
    for(int i=2;i<=n;i++)
    {
        if(md[m]!=val[r[i]]) md[++m]=val[r[i]];
        val[r[i]]=m;
    }
}
