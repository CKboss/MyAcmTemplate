/*
最大势求完美消除序列.
求出后从前往后做一遍检查:
v1....vn
与vi相连的点vj1....vjm
判断vj1是否可以与vj1+1...vjm相连

弦图的最小染色和最大独立集可由贪心得到
*/

typedef pair<int,int> pII;  
  
int n,m;  
vector<int> G[maxn];  
  
int lab[maxn];  
int R[maxn];  
int seq[maxn];  
  
priority_queue<pII> q;  
  
void MCS()  
{  
    memset(lab,0,sizeof(lab));  
    memset(R,-1,sizeof(R));  
    for(int i=1;i<=n;i++) q.push(make_pair(0,i));  
  
    for(int i=n;i>=1;)  
    {  
        pII u=q.top(); q.pop();  
        int id=u.second;  
        if(R[id]!=-1) continue;  
        seq[i]=id; R[id]=i--;  
        for(int j=0,sz=G[id].size();j<sz;j++)  
        {  
            int v=G[id][j];  
            if(R[v]!=-1) continue;  
            lab[v]++;  
            q.push(make_pair(lab[v],v));  
        }  
    }  
}  
  
