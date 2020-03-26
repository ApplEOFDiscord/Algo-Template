#include<bits/stdc++.h>
#define P pair<int,int>
using namespace std;

const int maxn=1e5+10;
int dfn[maxn],low[maxn],id[maxn],clk,cnt;
vector<int> g[maxn],bcc[maxn];
stack<int> st;

int tarjan(int u,int pre)
{
    dfn[u]=low[u]=++clk;
    st.push(u);
    for(auto v:g[u]){
        if(v==pre) continue;
        if(!dfn[v]) low[u]=min(low[u],tarjan(v,u));
        else if(dfn[v]<dfn[u]) low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]){
        cnt++;int un;
        do{
            un=st.top();st.pop();
            bcc[cnt].push_back(un),id[un]=cnt;
        }while(un!=u);
    }
    return low[u];
}