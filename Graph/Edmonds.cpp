/*
  URAL 1099 一般图最大匹配 Edmonds  带花树
  复杂度 n^3
*/


#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn=250;

/*******************************************/

struct Edge
{
  int to,next;
}edge[maxn*maxn];

int Adj[maxn],Size;

void init()
{
  memset(Adj,-1,sizeof(Adj)); Size=0;
}

void add_edge(int u,int v)
{
  edge[Size].to=v; edge[Size].next=Adj[u]; Adj[u]=Size++;
}

/*******************************************/

int n;
int Match[maxn];
bool G[maxn][maxn];
int Start,Finish,NewBase;
int Father[maxn],Base[maxn];
bool InQueue[maxn],InPath[maxn],InBlossom[maxn];
int Count;
queue<int> q;


int FindCommonAncestor(int u,int v)
{
  memset(InPath,false,sizeof(InPath));
  while(true)
    {
      u=Base[u];
      InPath[u]=true;
      if(u==Start) break;
      u=Father[Match[u]];
    }
  while(true)
    {
      v=Base[v];
      if(InPath[v]) break;
      v=Father[Match[v]];
    }
  return v;
}

void ResetTrace(int u)
{
  int v;
  while(Base[u]!=NewBase)
    {
      v=Match[u];
      InBlossom[Base[u]]=InBlossom[Base[v]]=true;
      u=Father[v];
      if(Base[u]!=NewBase) Father[u]=v;
    }
}

void BlosomContract(int u,int v)
{
  NewBase=FindCommonAncestor(u,v);
  memset(InBlossom,false,sizeof(InBlossom));
  ResetTrace(u);
  ResetTrace(v);
  if(Base[u]!=NewBase) Father[u]=v;
  if(Base[v]!=NewBase) Father[v]=u;
  for(int tu=1;tu<=n;tu++)
    {
      if(InBlossom[Base[tu]])
        {
          Base[tu]=NewBase;
          if(!InQueue[tu])
            {
              q.push(tu);
              InQueue[tu]=true;
            }
        }
    }
}

void FindAugmentingPath()
{
  memset(InQueue,false,sizeof(InQueue));
  memset(Father,0,sizeof(Father));
  for(int i=1;i<=n;i++)
    Base[i]=i;
  while(!q.empty()) q.pop();
  q.push(Start); InQueue[Start]=true;
  Finish=0;

  while(!q.empty())
    {
      int u=q.front(); //InQueue[u]=false;
      q.pop();
      for(int i=Adj[u];~i;i=edge[i].next)
        {
          int v=edge[i].to;
          if((Base[u]!=Base[v])&&Match[u]!=v)
            {
              if(v==Start||(Match[v]>0&&Father[Match[v]]>0))
                BlosomContract(u,v);
              else if(Father[v]==0)
                {
                  Father[v]=u;
                  if(Match[v]>0)
                    {
                      q.push(Match[v]);
                      InQueue[Match[v]]=true;
                    }
                  else
                    {
                      Finish=v;
                      return ;
                    }
                }
            }
        }
    }
}

void AugmentPath()
{
  int u,v,w;
  u=Finish;
  while(u>0)
    {
      v=Father[u];
      w=Match[v];
      Match[v]=u;
      Match[u]=v;
      u=w;
    }
}

void Edmonds()
{
  memset(Match,0,sizeof(Match));
  for(int u=1;u<=n;u++)
    {
      if(Match[u]==0)
        {
          Start=u;
          FindAugmentingPath();
          if(Finish>0) AugmentPath();
        }
    }
}

void PrintMatch()
{
  Count=0;
  for(int i=1;i<=n;i++)
    {
      if(Match[i]) Count++;
    }
  printf("%d\n",Count);
  for(int u=1;u<=n;u++)
    {
      if(u<Match[u])
        printf("%d %d\n",u,Match[u]);
    }
}

int main()
{
  //freopen("data.in","r",stdin);
  while(scanf("%d",&n)!=EOF)
    {
      init();
      memset(G,false,sizeof(G));
      int u,v;
      while(scanf("%d%d",&u,&v)!=EOF)
        {
          if(G[u][v]==true) continue;
          G[u][v]=G[v][u]=true;
          add_edge(u,v);
          add_edge(v,u);
        }
      Edmonds();
      PrintMatch();
    }
  return 0;
}

