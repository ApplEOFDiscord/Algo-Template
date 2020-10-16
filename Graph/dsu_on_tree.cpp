#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
int sz[maxn],son[maxn];
vector<int> g[maxn];

void dfs(int u,int pre)
{
    sz[u]=1;
    for(auto v:g[u]){
        if(v==pre) continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]) son[u]=v;
    }
}

vector<int> *vec[maxn];

inline void update(int x,int op)
{
    //加入或删除点ｘ的信息
}

void calc(int u,int pre,bool keep)
{
    for(auto v:g[u]){
        if(v==pre||v==son[u]) continue;
        calc(v,u,0);
    }
    if(son[u]) calc(son[u],u,1),vec[u]=vec[son[u]];
    else vec[u]=new vector<int>();
    vec[u]->push_back(u);
    update(u,1);
    for(auto v:g[u]){
        if(v==pre||v==son[u]) continue;
        for(auto x:*vec[v]){
            update(x,1);
            vec[u]->push_back(x);
        }
    }
    //计算点ｕ的答案
    if(!keep){
        for(auto v:*vec[u]) update(v,-1);
    }
}