/*

改段求段操作，需要两个辅助数组b，c
b记录从a[1..i]被加了几次，是向后更新的
c记录从a[1..i]被加的和，向前更新的 c[i]=b[i]*i

根据加入位置对a[i]的影响：
a[1..i]= sumB(i)*i+sumC(i-1)

*/

int lowbit(int x)
{
    return x&(-x);
}
void add_b(int id,int p,LL v)
{
    for(int i=p;i;i-=lowbit(i)) B[id][i]+=v;
}
void add_c(int id,int p,LL v)
{
    for(int i=p;i<=nm;i+=lowbit(i)) C[id][i]+=v*p;
}
LL sum_b(int id,int p)
{
    LL sum=0;
    for(int i=p;i<=nm;i+=lowbit(i)) sum+=B[id][i];
    return sum;
}
LL sum_c(int id,int p)
{
    LL sum=0;
    for(int i=p;i;i-=lowbit(i)) sum+=C[id][i];
    return sum;
}
void ADD(int id,int l,int r,LL v)
{
    add_b(id,r,v);
    add_c(id,r,v);
    if(l-1)
    {
        add_b(id,l-1,-v);
        add_c(id,l-1,-v);
    }
}
LL sUm(int id,int p)
{
    if(p)   return sum_b(id,p)*p+sum_c(id,p-1);
    else return 0;
}
LL SUM(int id,int l,int r)
{
    return sUm(id,r)-sUm(id,l-1);
}
