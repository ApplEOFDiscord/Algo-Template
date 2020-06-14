#include<bits/stdc++.h>
#define P pair<int,int>
using namespace std;

const int maxn=1e5+10;
const int maxm=2e5+10;
int n,m,cur[maxn];
int deg[maxn],in[maxn],out[maxn];
bool vis[maxm<<1];
vector<P> g[maxn];
vector<int> path;

void dfs_bidir(int u)
{
    for(int &i=cur[u];i<g[u].size();i++){
        int v=g[u][i].first,id=g[u][i].second;
        if(!vis[id]){
            vis[id]=vis[id^1]=true;
            dfs_bidir(v);
            path.push_back(id&1?-id/2:id/2);
        }
    }
}

bool euler_bidir()
{
    for(int i=1;i<=n;i++)
        if(deg[i]&1) return false;
    for(int i=1;i<=n;i++)
        if(deg[i]){
            dfs_bidir(i);break;
        }
    if(path.size()!=m) return false;
    reverse(path.begin(),path.end());
    return true;
}

void dfs_dir(int u)
{
    for(int &i=cur[u];i<g[u].size();i++){
        int v=g[u][i].first,id=g[u][i].second;
        if(!vis[id]){
            vis[id]=true;
            dfs_dir(v);
            path.push_back(id);
        }
    }
}

bool euler_dir()
{
    for(int i=1;i<=n;i++)
        if(in[i]!=out[i]) return false;
    for(int i=1;i<=n;i++)
        if(in[i]){
            dfs_dir(i);break;
        }
    if(path.size()!=m) return false;
    reverse(path.begin(),path.end());
    return true;
}
