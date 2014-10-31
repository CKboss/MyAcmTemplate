/*  HDOJ 4010 */
//切割、合并子树,路径上所有点的点权增加一个值,查询路径上点权的最大值
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn=330000;

int ch[maxn][2],pre[maxn],key[maxn];
int add[maxn],rev[maxn],Max[maxn];
bool rt[maxn];

void update_add(int r,int d)
{
  if(!r) return ;
  key[r]+=d;
  add[r]+=d;
  Max[r]+=d;
}

void update_rev(int r)
{
  if(!r) return ;
  swap(ch[r][0],ch[r][1]);
  rev[r]^=1;
}

void push_down(int r)
{
  if(add[r])
    {
      update_add(ch[r][0],add[r]);
      update_add(ch[r][1],add[r]);
      add[r]=0;
    }
  if(rev[r])
    {
      update_rev(ch[r][0]);
      update_rev(ch[r][1]);
      rev[r]=0;
    }
}

void push_up(int r)
{
  Max[r]=max(max(Max[ch[r][0]],Max[ch[r][1]]),key[r]);
}

void Rotate(int x)
{
  int y=pre[x],kind=(ch[y][1]==x);
  ch[y][kind]=ch[x][!kind];
  pre[ch[y][kind]]=y;
  pre[x]=pre[y];
  pre[y]=x;
  ch[x][!kind]=y;
  if(rt[y]) rt[y]=false,rt[x]=true;
  else ch[pre[x]][ch[pre[x]][1]==y]=x;
  push_up(y);
}

void P(int r)
{
  if(!rt[r]) P(pre[r]);
  push_down(r);
}

void Splay(int r)
{
  P(r);
  while(!rt[r])
    {
      int f=pre[r],ff=pre[f];
      if(rt[f]) Rotate(r);
      else if((ch[ff][1]==f)==(ch[f][1]==r)) Rotate(f),Rotate(r);
      else Rotate(r),Rotate(r);
    }
  push_up(r);
}

int Access(int x) //打通x到根的路径
{
  int y=0;
  for(;x;x=pre[y=x])
    {
      Splay(x);
      rt[ch[x][1]]=true; rt[ch[x][1]=y]=false;
      push_up(x);
    }
  return y;
}

bool judge(int u,int v)
{
  while(pre[u]) u=pre[u];
  while(pre[v]) v=pre[v];
  return u==v;
}

void mroot(int r)
{
  Access(r);
  Splay(r);
  update_rev(r);
}

void lca(int &u,int &v)
{
  Access(v); v=0;
  while(u)
    {
      Splay(u);
      if(!pre[u]) return ;
      rt[ch[u][1]]=true;
      rt[ch[u][1]=v]=false;
      push_up(u);
      u=pre[v=u];
    }
}

void link(int u,int v)
{
  if(judge(u,v))
    {
      puts("-1");
      return ;
    }
  mroot(u);
  pre[u]=v;
}

void cut(int u,int v)
{
  if(u==v||!judge(u,v))
    {
      puts("-1");
      return ;
    }
  mroot(u);
  Splay(v);
  pre[ch[v][0]]=pre[v];
  pre[v]=0;
  rt[ch[v][0]]=true;
  ch[v][0]=0;
  push_up(v);
}

void Add(int u,int v,int w)
{
  if(!judge(u,v))
    {
      puts("-1"); return ;
    }
  lca(u,v);
  update_add(ch[u][1],w);
  update_add(v,w);
  key[u]+=w;
  push_up(u);
}

void query(int u,int v)
{
  if(!judge(u,v))
    {
      puts("-1");
      return ;
    }
  lca(u,v);
  printf("%d\n",max(max(Max[v],Max[ch[u][1]]),key[u]));
}

struct Edge
{
  int to,next;
}edge[maxn*2];

int Adj[maxn],Size=0;

void init()
{
  memset(Adj,-1,sizeof(Adj)); Size=0;
}

void add_edge(int u,int v)
{
  edge[Size].to=v;
  edge[Size].next=Adj[u];
  Adj[u]=Size++;
}

void dfs(int u)
{
  for(int i=Adj[u];~i;i=edge[i].next)
    {
      int v=edge[i].to;
      if(pre[v]!=0) continue;
      pre[v]=u;
      dfs(v);
    }
}
int n;

int main()
{
  while(scanf("%d",&n)!=EOF)
    {
      init();
      for(int i=0;i<n+10;i++)
        {
          pre[i]=0; ch[i][0]=ch[i][1]=0;
          rev[i]=0; add[i]=0; rt[i]=true;
        }

      for(int i=0;i<n-1;i++)
        {
          int u,v;
          scanf("%d%d",&u,&v);
          add_edge(u,v);
          add_edge(v,u);
        }
      pre[1]=-1; dfs(1); pre[1]=0;

      for(int i=1;i<=n;i++)
        {
          scanf("%d",key+i);
          Max[i]=key[i];
        }

      int q;
      scanf("%d",&q);
      while(q--)
        {
          int op;
          scanf("%d",&op);
          if(op==1)
            {
              int x,y;
              scanf("%d%d",&x,&y);
              link(x,y);
            }
          else if(op==2)
            {
              int x,y;
              scanf("%d%d",&x,&y);
              cut(x,y);
            }
          else if(op==3)
            {
              int x,y,w;
              scanf("%d%d%d",&w,&x,&y);
              Add(x,y,w);
            }
          else if(op==4)
            {
              int x,y;
              scanf("%d%d",&x,&y);
              query(x,y);
            }
        }
      putchar(10);
    }
  return 0;
}
/* Tree */
//cut link add mul size rev query

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long int LL;
const int maxn=100100;
const LL mod=51061;
int ch[maxn][2],pre[maxn];
bool rev[maxn],rt[maxn];
LL size[maxn],key[maxn],add[maxn],mul[maxn],sum[maxn];
void update_add(int r,LL d)
{
  if(!r) return ;
  if(d==0) return ;
  key[r]=(key[r]+d)%mod;
  add[r]=(add[r]+d)%mod;
  sum[r]=(size[r]*d+sum[r])%mod;
}
void update_mul(int r,LL d)
{
  if(!r) return ;
  if(d==1) return ;
  sum[r]=(sum[r]*d)%mod;
  key[r]=(key[r]*d)%mod;
  mul[r]=(mul[r]*d)%mod;
  add[r]=(add[r]*d)%mod;
}
void update_rev(int r)
{
  if(!r) return ;
  swap(ch[r][0],ch[r][1]);
  rev[r]=rev[r]^1;
}
void push_down(int r)
{
  if(!r) return ;
  if(rev[r])
    {
      if(ch[r][0]) update_rev(ch[r][0]);
      if(ch[r][1]) update_rev(ch[r][1]);
      rev[r]=0;
    }
  if(mul[r]!=1)
    {
      if(ch[r][0]) update_mul(ch[r][0],mul[r]);
      if(ch[r][1]) update_mul(ch[r][1],mul[r]);
      mul[r]=1;
    }
  if(add[r])
    {
      if(ch[r][0]) update_add(ch[r][0],add[r]);
      if(ch[r][1]) update_add(ch[r][1],add[r]);
      add[r]=0;
    }
 }
void push_up(int r)
{
  sum[r]=key[r]%mod;
  size[r]=1;
  if(ch[r][0])
    {
      sum[r]=(sum[r]+sum[ch[r][0]])%mod;
      size[r]+=size[ch[r][0]];
    }
  if(ch[r][1])
    {
      sum[r]=(sum[r]+sum[ch[r][1]])%mod;
      size[r]+=size[ch[r][1]];
    }
}
void Rotate(int x)
{
  int y=pre[x],kind=ch[y][1]==x;
  ch[y][kind]=ch[x][!kind];
  pre[ch[y][kind]]=y;
  pre[x]=pre[y];
  pre[y]=x;
  ch[x][!kind]=y;
  if(rt[y]) rt[y]=false,rt[x]=true;
  else ch[pre[x]][ch[pre[x]][1]==y]=x;
  push_up(y);
}
void P(int r)
{
  if(!rt[r]) P(pre[r]);
  push_down(r);
}
void Splay(int r)
{
  P(r);
  while(!rt[r])
    {
      int f=pre[r],ff=pre[f];
      if(rt[f]) Rotate(r);
      else if((ch[ff][1]==f)==(ch[f][1]==r)) Rotate(f),Rotate(r);
      else Rotate(r),Rotate(r);
    }
  push_up(r);
}
int Access(int x)
{
  int y=0;
  for(;x;x=pre[y=x])
    {
      Splay(x);
      rt[ch[x][1]]=true; rt[ch[x][1]=y]=false;
      push_up(x);
    }
  return y;
}
void mroot(int r)
{
  Access(r);
  Splay(r);
  update_rev(r);
}
void link(int u,int v)
{
  mroot(u);
  pre[u]=v;
}
void cut(int u,int v)
{
  mroot(u);
  Splay(v);
  pre[ch[v][0]]=pre[v];
  pre[v]=0;
  rt[ch[v][0]]=true;
  ch[v][0]=0;
  push_up(v);
}
void Add(int u,int v,LL d)
{
  mroot(u);
  Access(v);
  Splay(v);
  update_add(v,d);
}
void Mul(int u,int v,LL d)
{
  mroot(u);
  Access(v);
  Splay(v);
  update_mul(v,d);
}
void debug();
void query(int u,int v)
{
  mroot(u);
  Access(v);
  Splay(v);
  //cout<<"size: "<<size[v]<<" sum: "<<sum[v]<<endl;
  printf("%lld\n",sum[v]);
}
struct Edge
{
  int to,next;
}edge[maxn*2];
int Adj[maxn],Size;

void add_edge(int u,int v)
{
  edge[Size].to=v; edge[Size].next=Adj[u]; Adj[u]=Size++;
}
int n,q;
void init()
{
  Size=0;
  for(int i=0;i<=n+10;i++)
    {
      Adj[i]=-1;
      ch[i][0]=ch[i][1]=0;
      pre[i]=0; rt[i]=true; rev[i]=false;
      key[i]=1; size[i]=1; add[i]=0; mul[i]=1; sum[i]=1;
    }
}
void dfs(int u)
{
  for(int i=Adj[u];~i;i=edge[i].next)
    {
      int v=edge[i].to;
      if(pre[v]!=0) continue;
      pre[v]=u;
      dfs(v);
    }
}
void showit(int x)
{
    if(x)
    {
        push_down(x);
        showit(ch[x][0]);
        printf("结点: %2d 左儿子: %2d 右儿子: %2d 父结点: %2d size: %2lld sum: %2lld key: %2lld\n",
               x,ch[x][0],ch[x][1],pre[x],size[x],sum[x],key[x]);
        showit(ch[x][1]);
    }
}
void debug()
{
  for(int i=0;i<=n;i++)
    {
      if(rt[i])
        {
          cout<<"ROOT: "<<i<<endl;
          showit(i);
          cout<<"..........\n";
        }
    }
}
int main()
{
  while(scanf("%d%d",&n,&q)!=EOF)
    {
      init();
      for(int i=0;i<n-1;i++)
        {
          int u,v;
          scanf("%d%d",&u,&v);
          add_edge(u,v); add_edge(v,u);
        }
      pre[1]=-1; dfs(1); pre[1]=0;
      //debug();
      char op[10];
      while(q--)
        {
          scanf("%s",op);
          if(op[0]=='+')
            {
              int u,v,c;
              scanf("%d%d%d",&u,&v,&c);
              Add(u,v,c);
            }
          else if(op[0]=='-')
            {
              int u1,v1,u2,v2;
              scanf("%d%d%d%d",&u1,&v1,&u2,&v2);
              cut(u1,v1);
              link(u2,v2);
            }
          else if(op[0]=='*')
            {
              int u,v,c;
              scanf("%d%d%d",&u,&v,&c);
              Mul(u,v,c);
            }
          else if(op[0]=='/')
            {
              int u,v;
              scanf("%d%d",&u,&v);
              query(u,v);
            }
          //debug();
        }
    }
  return 0;
}
