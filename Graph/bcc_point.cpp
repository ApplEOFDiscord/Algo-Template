#include<bits/stdc++.h>
#define P pair<int,int>
using namespace std;

const int maxn=1e5+10;
int dfn[maxn],low[maxn],id[maxn],clk,cnt;
bool cut[maxn];  
vector<int> g[maxn],bcc[maxn];
stack<P> st;

//如果图中有重边,pre应保存边的编号(从父亲到当前点)
int tarjan(int u,int pre)
{
    dfn[u]=low[u]=++clk;
    int son=0;
    for(auto v:g[u]){
        if(v==pre) continue;
        if(!dfn[v]){
            st.push(P{u,v});son++;  //点双连通分量的边不会重复，因此把边入栈
            low[u]=min(low[u],tarjan(v,u));
            if(low[v]>=dfn[u]){
                cut[u]=true;cnt++;
                int un,vn;
                do{
                    P x=st.top();st.pop();
                    un=x.first,vn=x.second;
                    if(id[un]!=cnt) bcc[cnt].push_back(un),id[un]=cnt;
                    if(id[vn]!=cnt) bcc[cnt].push_back(vn),id[vn]=cnt;
                }while(un!=u||vn!=v);
            }
        }
        else if(dfn[v]<dfn[u]){
            st.push(P{u,v});
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(pre==-1&&son<=1) cut[u]=false;
    return low[u];
}