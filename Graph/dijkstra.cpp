#include<bits/stdc++.h>
#define LL long long
#define P pair<int,int>
using namespace std;

const int maxn=1e5+10;
const int INF=1e9;
int d[maxn];
bool vis[maxn];
vector<P> g[maxn];

void dijkstra(int n,int s)
{
    priority_queue<P,vector<P>,greater<P>> q;
    for(int i=1;i<=n;i++) d[i]=INF,vis[i]=0;
    d[s]=0,q.push(P{0,s});
    while(!q.empty()){
        P x=q.top();q.pop();
        int u=x.second;
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:g[u]){
            int v=e.first,w=e.second;
            if(d[u]+w<d[v]){
                d[v]=d[u]+w;
                q.push(P{d[v],v});
            }
        }
    }
}