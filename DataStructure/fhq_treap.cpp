#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
int ch[maxn][2],val[maxn],rnd[maxn],sz[maxn],tot,rt,x,y,z;

inline void pushup(int o) { sz[o]=sz[ch[o][0]]+sz[ch[o][1]]+1; }

void split(int o,int v,int &x,int &y)
{
    if(!o) { x=y=0;return; }
    if(v<val[o]) y=o,split(ch[o][0],v,x,ch[o][0]);
    else x=o,split(ch[o][1],v,ch[o][1],y);
    pushup(o);
}

int merge(int x,int y)
{
    if(!x||!y) return x+y;
    if(rnd[x]<rnd[y]){
        ch[x][1]=merge(ch[x][1],y);
        pushup(x);return x; 
    }
    else{ 
        ch[y][0]=merge(x,ch[y][0]);
        pushup(y);return y; 
    }
}

inline int create(int v) { sz[++tot]=1,val[tot]=v,rnd[tot]=rand();return tot; }

void ins(int v)
{
    split(rt,v,x,y);
    rt=merge(merge(x,create(v)),y);
}

void del(int v)
{
    split(rt,v-1,x,y);split(y,v,y,z);
    y=merge(ch[y][0],ch[y][1]);
    rt=merge(merge(x,y),z);
}

int rnk(int v)
{
    split(rt,v-1,x,y);
    int res=sz[x]+1;
    rt=merge(x,y);
    return res;
}

int kth(int o,int k)
{
    while(1){
        if(k==sz[ch[o][0]]+1) return val[o];
        else if(k<=sz[ch[o][0]]) o=ch[o][0];
        else k-=sz[ch[o][0]]+1,o=ch[o][1];
    }
}

int pre(int v)
{
    split(rt,v-1,x,y);
    int res=kth(x,sz[x]);
    rt=merge(x,y);
    return res;
}

int nxt(int v)
{
    split(rt,v,x,y);
    int res=kth(y,1);
    rt=merge(x,y);
    return res;
}