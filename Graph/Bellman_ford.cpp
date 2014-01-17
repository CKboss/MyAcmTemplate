/*
bellmanford：时间复杂度要求不高的最短/长路，可以判断负/正环
松弛（V-1）遍，然后检测一下负环  O(E*V）
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn=15000;
const int INF=0x3f3f3f3f;

typedef struct Edge
{
    int u,v,cost;
}Edge;

Edge edge[maxn];
int dist[maxn],pre[maxn],nodenum,edgenum,original;

bool Bellman_Ford()
{
    for(int i=1;i<=nodenum;i++)
        dist[i]=(i==original)?0:INF;

    for(int i=1;i<nodenum;i++)
    {
        bool flag=false;
        for(int j=0;j<edgenum;j++)
        {
            if(dist[edge[j].v]>dist[edge[j].u]+edge[j].cost)
            {
                flag=true;
                dist[edge[j].v]=dist[edge[j].u]+edge[j].cost;
                pre[edge[j].v]=edge[j].u;
            }
        }
        if(!flag) return false;
    }

    bool flag=true;
    for(int i=1;i<=edgenum;i++)
    {
        if(dist[edge[i].v]>dist[edge[i].u]+edge[i].cost)
        {
            flag=0; break;
        }
    }
    return flag;
}


int main()
{
    return 0;
}

