#include<bits/stdc++.h>
#define P pair<int,int>
using namespace std;

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
