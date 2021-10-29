#include<bits/stdc++.h>
#define P pair<int,int>
using namespace std;

const int maxn=400+10;
const int INF=0x3f3f3f3f;
int n,m,d[maxn],p[maxn],a[maxn],h[maxn],tot,s,t;
bool vis[maxn];
vector<int> g[maxn];

struct edge
{
  int u,v,cap,flow,cost;
  edge(int u,int v,int cap,int flow,int cost):u(u),v(v),cap(cap),flow(flow),cost(cost) {}
};
vector<edge> all;

void addedge(int u,int v,int cap,int flow,int cost)
{
  all.push_back(edge{u,v,cap,0,cost});
  all.push_back(edge{v,u,0,0,-cost});
  tot=all.size();
  g[u].push_back(tot-2);
  g[v].push_back(tot-1);
}

void spfa()
{
  queue<int> q;
  memset(h,0x3f,sizeof(h));
  h[s]=0,vis[s]=1;q.push(s);
  while(!q.empty()){
    int u=q.front();q.pop();
    vis[u]=0;
    for(int i:g[u]){
      edge& e=all[i];
      int v=e.v,cap=e.cap,flow=e.flow,cost=e.cost;
      if(cap>flow&&h[v]>h[u]+cost){
        h[v]=h[u]+cost;
        if(!vis[v]) q.push(v),vis[v]=1;
      }
    }
  }
}

bool dijkstra(int &flow,int &cost)
{
  priority_queue<P,vector<P>,greater<P>> q;
  for(int i=1;i<=n;i++) d[i]=INF,vis[i]=0;
  d[s]=0,p[s]=0,a[s]=INF;q.push(P{0,s});
  while(!q.empty()){
    int u=q.top().second;q.pop();
    if(vis[u]) continue;
    vis[u]=1;
    for(int i:g[u]){
      edge& e=all[i];
      int v=e.v,cap=e.cap,flow=e.flow,cost=e.cost;
      if(cap>flow&&d[v]>d[u]+cost+h[u]-h[v]){
        d[v]=d[u]+cost+h[u]-h[v],p[v]=i,a[v]=min(a[u],cap-flow);
        q.push(P{d[v],v});
      }
    }
  }
  if(d[t]==INF) return 0;
  for(int i=1;i<=n;i++) h[i]+=d[i];
  flow+=a[t],cost+=h[t]*a[t];
  int u=t;
  while(u!=s){
    all[p[u]].flow+=a[t],all[p[u]^1].flow-=a[t];
    u=all[p[u]].u;
  }
  return 1;
}

P mcmf()
{
  int flow=0,cost=0;
  spfa();
  while(dijkstra(flow,cost));
  return P{flow,cost};
}

/*
const int maxn=400+10;
const int INF=0x3f3f3f3f;
int d[maxn],p[maxn],a[maxn],tot,s,t;
bool inq[maxn];
vector<int> g[maxn];
queue<int> q;

struct edge
{
    int u,v,cap,flow,cost;
    edge(int u,int v,int cap,int flow,int cost): u(u),v(v),cap(cap),flow(flow),cost(cost) {}
};
vector<edge> all;

void addedge(int u,int v,int cap,int cost)
{
    all.push_back(edge{u,v,cap,0,cost});
    all.push_back(edge{v,u,0,0,-cost});
    tot=all.size();
    g[u].push_back(tot-2);
    g[v].push_back(tot-1);
}

bool spfa(int &flow,int &cost)
{
    memset(d,0x3f,sizeof(d));
    q.push(s);
    d[s]=0,inq[s]=1,p[s]=0,a[s]=INF;
    while(!q.empty()){
        int u=q.front();q.pop();
        inq[u]=0;
        for(auto i:g[u]){
            edge& e=all[i];
            int v=e.v,cap=e.cap,flow=e.flow,cost=e.cost;
            if(cap>flow&&d[v]>d[u]+cost){
                d[v]=d[u]+cost,p[v]=i,a[v]=min(a[u],cap-flow);
                if(!inq[v]) q.push(v),inq[v]=1;
            }
        }
    }
    if(d[t]==INF) return 0;
    flow+=a[t],cost+=d[t]*a[t];
    int u=t;
    while(u!=s){
        all[p[u]].flow+=a[t],all[p[u]^1].flow-=a[t];
        u=all[p[u]].u;
    }
    return 1;
}

P mcmf()
{
    int flow=0,cost=0;
    while(spfa(flow,cost));
    return P{flow,cost}; 
}
*/