#include<bits/stdc++.h>
using namespace std;

const int maxn=400;
int match[maxn];
bool vis[maxn];
vector<int> g[maxn];

bool dfs(int u)
{
    for(auto v:g[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v]||dfs(match[v])){
            match[v]=u;return 1;
        }
    }
    return 0;
}