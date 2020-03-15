#include<bits/stdc++.h>
#define ls o<<1
#define rs o<<1|1
using namespace std;

const int maxn=1e5+10;
int sz[maxn],top[maxn],son[maxn],dep[maxn],fa[maxn],dfn[maxn],rnk[maxn],n,clk;
int val[maxn],len[maxn<<2],sum[maxn<<2],add[maxn<<2];
vector<int> g[maxn];

void dfs1(int u,int pre)
{
    sz[u]=1;
    for(auto v:g[u]){
        if(v==pre) continue;
        dep[v]=dep[u]+1,fa[v]=u;
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]) son[u]=v;
    }
}

void dfs2(int u,int t)
{
    top[u]=t;
    dfn[u]=++clk;rnk[dfn[u]]=u;
    if(!son[u]) return;
    dfs2(son[u],t);
    for(auto v:g[u]){
        if(v==son[u]||v==fa[u]) continue;
        dfs2(v,v);
    }
}

void build(int o,int l,int r)
{   
    len[o]=r-l+1;
    if(l==r){
        sum[o]=val[rnk[l]];return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid),build(rs,mid+1,r);
    sum[o]=sum[ls]+sum[rs];
}

void pushdown(int o)
{
    if(!add[o]) return;
    add[ls]+=add[o],sum[ls]+=add[o]*len[ls];
    add[rs]+=add[o],sum[rs]+=add[o]*len[rs];
    add[o]=0;
}

void update(int o,int l,int r,int ll,int rr,int v)
{
    if(ll<=l&&r<=rr){
        add[o]+=v,sum[o]+=v*len[o];
        return;
    }
    pushdown(o);
    int mid=(l+r)>>1;
    if(ll<=mid) update(ls,l,mid,ll,rr,v);
    if(rr>mid) update(rs,mid+1,r,ll,rr,v);
    sum[o]=sum[ls]+sum[rs];
}

int query(int o,int l,int r,int ll,int rr)
{
    if(ll<=l&&r<=rr) return sum[o];
    pushdown(o);
    int mid=(l+r)>>1,res=0;
    if(ll<=mid) res+=query(ls,l,mid,ll,rr);
    if(rr>mid) res+=query(rs,mid+1,r,ll,rr);
    return res;
}

void updatepath(int x,int y,int v)
{
    while(top[x]!=top[y]){
        if(dep[top[x]]>=dep[top[y]]) update(1,1,n,dfn[top[x]],dfn[x],v),x=fa[top[x]];
        else update(1,1,n,dfn[top[y]],dfn[y],v),y=fa[top[y]];
    }
    if(dep[x]<=dep[y]) update(1,1,n,dfn[x],dfn[y],v);
    else update(1,1,n,dfn[y],dfn[x],v);
}

int querypath(int x,int y)
{
    int res=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]>=dep[top[y]]) res+=query(1,1,n,dfn[top[x]],dfn[x]),x=fa[top[x]];
        else res+=query(1,1,n,dfn[top[y]],dfn[y]),y=fa[top[y]];
    }
    if(dep[x]<=dep[y]) res+=query(1,1,n,dfn[x],dfn[y]);
    else res+=query(1,1,n,dfn[y],dfn[x]);
    return res;
}