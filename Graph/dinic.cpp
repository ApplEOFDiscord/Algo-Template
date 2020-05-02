#include<bits/stdc++.h>
using namespace std;

const int maxn=400+10;
const int INF=1e9;
int tot,s,t,cur[maxn],d[maxn];
bool vis[maxn];
vector<int> g[maxn];
queue<int> q;

struct edge
{
    int u,v,cap,flow;
    edge(int u,int v,int cap,int flow): u(u),v(v),cap(cap),flow(flow) {}
};
vector<edge> all;

void addedge(int u,int v,int cap)
{
    all.push_back(edge{u,v,cap,0});
    all.push_back(edge{v,u,0,0});
    tot=all.size();
    g[u].push_back(tot-2);
    g[v].push_back(tot-1);
}

bool bfs()
{
    memset(vis,0,sizeof(vis));
    q.push(s);
    d[s]=0,vis[s]=true;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto i:g[u]){
            edge& e=all[i];
            int v=e.v,cap=e.cap,flow=e.flow;
            if(!vis[v]&&cap>flow){
                vis[v]=true;
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
    return vis[t];
}

int dfs(int u,int a)
{
    if(u==t||a==0) return a;
    int flow=0,f;
    for(int& i=cur[u];i<g[u].size();i++){
        edge& e=all[g[u][i]];
        if(d[u]+1==d[e.v]&&(f=dfs(e.v,min(a,e.cap-e.flow)))>0){
            e.flow+=f;
            all[g[u][i]^1].flow-=f;
            flow+=f;
            a-=f;
            if(a==0) break;
        }
    }
    return flow;
}

int maxflow()
{
    int flow=0;
    while(bfs()){
        memset(cur,0,sizeof(cur));
        flow+=dfs(s,INF);
    }
    return flow;
}