#pragma comment(linker,"/STACK:102400000,102400000") 
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<queue>
#define MAXN 200005
#define MAXM 200005
#define oo 1000000007
#define ll long long
using namespace std;
int X[MAXN];
struct Dinic
{
      struct node 
      {
             int x,y,c,next;
      }line[MAXM];   
      int Lnum,_next[MAXN],dis[MAXN];
      void initial(int n) 
      {
             for (int i=0;i<=n;i++) _next[i]=-1;
             Lnum=-1;
      } 
      void addline(int x,int y,int c)
      {
             line[++Lnum].next=_next[x],_next[x]=Lnum;
             line[Lnum].x=x,line[Lnum].y=y,line[Lnum].c=c;
             line[++Lnum].next=_next[y],_next[y]=Lnum;
             line[Lnum].x=y,line[Lnum].y=x,line[Lnum].c=c;             
      }
      bool BFS(int s,int e)
      { 
             queue<int> Q;
             while (!Q.empty()) Q.pop();
             memset(dis,0,sizeof(dis));
             dis[s]=1;
             Q.push(s);
             while (!Q.empty())
             {
                   int h,k;
                   h=Q.front(),Q.pop();
                   if (h==e) return dis[e];
                   for (k=_next[h];k!=-1;k=line[k].next)
                      if (line[k].c && !dis[line[k].y])
                         dis[line[k].y]=dis[h]+1,Q.push(line[k].y);                 
             } 
             return false;
      }
      int dfs(int x,int flow,int e)  
      {     
             if (x==e) return flow;   
             int temp,cost=0;  
             for (int k=_next[x];k!=-1;k=line[k].next)  
             if (line[k].c && dis[line[k].y]==dis[x]+1)  
             {  
                    temp=dfs(line[k].y,min(flow-cost,line[k].c),e);   
                    if (temp)  
                    {  
                           line[k].c-=temp,line[k^1].c+=temp;  
                           cost+=temp;  
                           if (flow==cost) return cost;  
                    }else dis[line[k].y]=-1;  
             }  
             return cost;  
      }  
      int MaxFlow(int s,int e)
      {
             int MaxFlow=0;
             while (BFS(s,e)) 
                MaxFlow+=dfs(s,oo,e); 
             return MaxFlow;
      }
}T;
int main()  
{          
       int n,m,s,e,i,x,y,c,cases; 
       scanf("%d",&cases);
       while (cases--)  
       {
               scanf("%d%d",&n,&m);
               s=e=1;
               for (i=1;i<=n;i++)
               {
                      scanf("%d%d",&x,&y);
                      X[i]=x;
                      if (x<X[s]) s=i;
                      if (x>X[e]) e=i;
               }
               T.initial(n);
               while (m--)
               {
                       scanf("%d%d%d",&x,&y,&c);
                       T.addline(x,y,c); 
               }
               printf("%d\n",T.MaxFlow(s,e));
       }
       return 0;  
}  
