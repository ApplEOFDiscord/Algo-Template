#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int maxn=1e5+10;
int sz[maxn],maxs[maxn],rt,tot;
bool vis[maxn];
vector<int> g[maxn];

void centroid(int u,int pre)
{
    sz[u]=1,maxs[u]=0;
    for(auto v:g[u]){
        if(v==pre||vis[v]) continue;
        centroid(v,u);
        sz[u]+=sz[v];
        maxs[u]=max(maxs[u],sz[v]);
    }
    maxs[u]=max(maxs[u],tot-sz[u]);
    if(maxs[u]<maxs[rt]) rt=u;
}

void calc(int u)
{
    //处理经过当前节点的路径信息
}

void divide(int u)
{
    vis[u]=1;calc(u);
    for(auto v:g[u]){
        if(vis[v]) continue;
        tot=sz[v],maxs[rt=0]=INF;
        centroid(v,u);centroid(rt,-1);
        divide(rt);
    }
}