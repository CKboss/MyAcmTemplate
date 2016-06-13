/*二维线段树  单点更新 最值,sum维护 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1

const int maxn=500;
const int INF=0x3f3f3f3f;

int Max[maxn<<2][maxn<<2];
int Sum[maxn<<2][maxn<<2];
int Min[maxn<<2][maxn<<2];
int xL,xR,yL,yR;
int n,m,mat[maxn][maxn];
int minV,maxV;

void pushUp(int xrt,int rt)
{
  Max[xrt][rt]=max(Max[xrt][rt<<1],Max[xrt][rt<<1|1]);
  Min[xrt][rt]=min(Min[xrt][rt<<1],Min[xrt][rt<<1|1]);
  Sum[xrt][rt]=Sum[xrt][rt<<1]+Sum[xrt][rt<<1|1];
}

void buildY(int xrt,int x,int l,int r,int rt)
{
  if(l==r)
    {
      /// x维度是确认的值
      if(x!=-1)
        {
          Max[xrt][rt]=Min[xrt][rt]=Sum[xrt][rt]=mat[x][l];
        }
      /// x维度是一个范围
      else if(x==-1)
        {
          Max[xrt][rt]=max(Max[xrt<<1][rt],Max[xrt<<1|1][rt]);
          Min[xrt][rt]=min(Min[xrt<<1][rt],Min[xrt<<1|1][rt]);
          Sum[xrt][rt]=Sum[xrt<<1][rt]+Sum[xrt<<1|1][rt];
        }
      return ;
    }

  int mid = (l+r)/2;
  buildY(xrt,x,lson); buildY(xrt,x,rson);
  pushUp(xrt,rt);
}

void buildX(int l,int r,int rt)
{
  if(l==r)
    {
      buildY(rt,l,1,m,1);
      return ;
    }

  int mid = (l+r)/2;
  buildX(lson); buildX(rson);
  buildY(rt,-1,1,m,1);
}

void updateY(int value,int xrt,int x,int l,int r,int rt)
{
  if(l==r)
    {
      /// x维度是确认的值
      if(x!=-1)
        {
          Max[xrt][rt]=Min[xrt][rt]=Sum[xrt][rt]=mat[x][l]=value;
        }
      /// x维度是一个范围
      else if(x==-1)
        {
          Max[xrt][rt]=max(Max[xrt<<1][rt],Max[xrt<<1|1][rt]);
          Min[xrt][rt]=min(Min[xrt<<1][rt],Min[xrt<<1|1][rt]);
          Sum[xrt][rt]=Sum[xrt<<1][rt]+Sum[xrt<<1|1][rt];
        }
      return ;
    }

  int mid = (l+r)/2;
  if(yL<=mid) updateY(value,xrt,x,lson);
  if(mid<yR) updateY(value,xrt,x,rson);
  pushUp(xrt,rt);
}

void updateX(int value,int l,int r,int rt)
{
  if(l==r)
    {
      updateY(value,rt,l,1,m,1);
      return ;
    }
  int mid = (l+r)/2;
  if(xL<=mid) updateX(value,lson);
  if(xR>mid) updateX(value,rson);
  updateY(value,rt,-1,1,m,1);
}

int queryY(int xrt,int x,int l,int r,int rt)
{
  if(yL<=l&&r<=yR)
    {
      minV=min(minV,Min[xrt][rt]);
      maxV=max(maxV,Max[xrt][rt]);
      return Sum[xrt][rt];
    }
  int mid = (l+r)/2;
  int ret=0;
  if(yL<=mid) ret+=queryY(xrt,x,lson);
  if(yR>mid) ret+=queryY(xrt,x,rson);
  return ret;
}

int queryX(int l,int r,int rt)
{
  if(l==r)
    {
      int ret=queryY(rt,l,1,m,1);
      return ret;
    }
  int mid = (l+r)/2;
  int ret=0;
  if(xL<=mid) ret+=queryX(lson);
  if(xR>mid) ret+=queryX(rson);
  return ret;
}

void showMat()
{
  puts("showMat:");
  for(int i=1;i<=n;i++)
    {
      for(int j=1;j<=m;j++)
        {
          minV=INF; maxV=-INF;
          xL=xR=i; yL=yR=j;
          queryX(1,n,1);
          cout<<minV<<" ";
          //cout<<mat[i][j]<<" ";
        }
      putchar(10);
    }
  puts("..............");
}

int main()
{

  n=3; m=4;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        mat[i][j]=(i-1)*m+j;
  buildX(1,n,1);

  int kind,V;
  while(cin>>kind)
    {
      int V;
      cin>>xL>>xR>>yL>>yR>>V;
      if(kind==0)
        {
          updateX(V,1,n,1);
          cout<<"update success!!"<<endl;
        }
      else if(kind==1)
        {
          minV = INF; maxV = -INF;
          int sumV = queryX(1,n,1);
          cout<<"minV: "<<minV<<" maxV: "<<maxV<<" sumV: "<<sumV<<endl;
        }
      showMat();
    }

  return 0;
}

