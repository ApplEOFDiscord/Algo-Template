#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
const int lgn=20;
int h[maxn],dfn[maxn],dep[maxn],fa[maxn][lgn+1],clk,k;
int s[maxn],top;
bool f[maxn];  //标记该点是否为关键点
vector<int> g[maxn],gn[maxn];

void init(int u,int pre)
{
    dfn[u]=++clk,dep[u]=dep[pre]+1,fa[u][0]=pre;
    for(int d=1;d<=lgn;d++) fa[u][d]=fa[fa[u][d-1]][d-1];
    for(auto v:g[u]){
        if(v==pre) continue;
        init(v,u);
    }
}

int lca(int a,int b)
{
    //...
}

bool cmp(int a,int b) { return dfn[a]<dfn[b]; }

void build_virtual()
{
    sort(h+1,h+k+1,cmp);
    s[top=1]=1;
    for(int i=1;i<=k;i++){
        if(h[i]==1) continue;
        int par=lca(s[top],h[i]);
        if(par!=s[top]){
            while(dfn[par]<dfn[s[top-1]]) gn[s[top-1]].push_back(s[top]),top--;
            if(dfn[par]==dfn[s[top-1]]) gn[par].push_back(s[top]),top--;
            else gn[par].push_back(s[top]),s[top]=par;
        }
        s[++top]=h[i];
    }
    for(int i=1;i<top;i++) gn[s[i]].push_back(s[i+1]);
}

