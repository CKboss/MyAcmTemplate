/*二维线段树  单点更新 最值,sum维护 */

#define lson l,m,rt<<1  
#define rson m+1,r,rt<<1|1  
  
const int maxn=1000;  
const int INF=(1<<30);  
  
int xL,xR,yL,yR,Value;  
int Max[maxn<<2][maxn<<2],Min[maxn<<2][maxn<<2];  
int n,mat[maxn][maxn];  
int minv,maxv;  
  
void pushup(int xrt,int rt)  
{  
    Max[xrt][rt]=max(Max[xrt][rt<<1],Max[xrt][rt<<1|1]);  
    Min[xrt][rt]=min(Min[xrt][rt<<1],Min[xrt][rt<<1|1]);  
}  
  
void buildY(int xrt,int x,int l,int r,int rt)  
{  
    if(l==r)  
    {  
        if(x==-1)  
        {  
            Max[xrt][rt]=max(Max[xrt<<1][rt],Max[xrt<<1|1][rt]);  
            Min[xrt][rt]=min(Min[xrt<<1][rt],Min[xrt<<1|1][rt]);  
        }  
        else  
        {  
            Max[xrt][rt]=Min[xrt][rt]=mat[x][l];  
        }  
        return ;  
    }  
    int m=(l+r)/2;  
    buildY(xrt,x,lson); buildY(xrt,x,rson);  
    pushup(xrt,rt);  
}  
  
void buildX(int l,int r,int rt)  
{  
    if(l==r)  
    {  
        buildY(rt,l,1,n,1);  
        return ;  
    }  
    int m=(l+r)/2;  
    buildX(lson); buildX(rson);  
    buildY(rt,-1,1,n,1);  
}  
  
void updateY(int xrt,int x,int l,int r,int rt)  
{  
    if(l==r)  
    {  
        if(x==-1)  
        {  
            Max[xrt][rt]=max(Max[xrt<<1][rt],Max[xrt<<1|1][rt]);  
            Min[xrt][rt]=min(Min[xrt<<1][rt],Min[xrt<<1|1][rt]);  
        }  
        else  
        {  
            Max[xrt][rt]=Min[xrt][rt]=Value;  
        }  
        return ;  
    }  
    int m=(l+r)/2;  
    if(yL<=m) updateY(xrt,x,lson);  
    else updateY(xrt,x,rson);  
    pushup(xrt,rt);  
}  
  
void updateX(int l,int r,int rt)  
{  
    if(l==r)  
    {  
        updateY(rt,l,1,n,1);  
        return ;  
    }  
    int m=(l+r)/2;  
    if(xL<=m) updateX(lson);  
    else updateX(rson);  
    updateY(rt,-1,1,n,1);  
}  
  
void queryY(int xrt,int l,int r,int rt)  
{  
    if(yL<=l&&r<=yR)  
    {  
        minv=min(minv,Min[xrt][rt]);  
        maxv=max(maxv,Max[xrt][rt]);  
        return ;  
    }  
    int m=(l+r)/2;  
    if(yL<=m) queryY(xrt,lson);  
    if(yR>m) queryY(xrt,rson);  
}  
  
void queryX(int l,int r,int rt)  
{  
    if(xL<=l&&r<=xR)  
    {  
        queryY(rt,1,n,1);  
        return ;  
    }  
    int m=(l+r)/2;  
    if(xL<=m) queryX(lson);  
    if(xR>m) queryX(rson);  
}  



／×××××××××××××××××××××××××××××／
buildX(1,n,1);  
xL=max(1,x-l);xR=min(n,x+l);  
yL=max(1,y-l);yR=min(n,y+l);  
minv=INF; maxv=-INF;  
queryX(1,n,1);  
Value=(minv+maxv)/2;  
printf("%d\n",Value);  
xL=x;yL=y;  
updateX(1,n,1);  


