#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
int fa[maxn],sz[maxn];
stack<int> st;

int find(int x)
{
    while(fa[x]!=x) x=fa[x];
    return x;
}

bool merge(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(fx==fy) return false;
    if(sz[fx]>sz[fy]) swap(fx,fy);
    fa[fx]=fy,sz[fy]+=sz[fx];
    st.push(fx);
    return true; 
}

void rollback()
{
    while(!st.empty()){
        int x=st.top();st.pop();
        sz[fa[x]]-=sz[x];
        fa[x]=x;
    }
}