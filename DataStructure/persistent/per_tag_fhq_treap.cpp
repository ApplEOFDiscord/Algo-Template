#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
int rt[maxn],ch[maxn*40][2],sz[maxn*40],val[maxn*40],rnd[maxn*40],sum[maxn*40],rev[maxn*40],tot;

inline int nodecpy(int x) { ch[++tot][0]=ch[x][0],ch[tot][1]=ch[x][1],sz[tot]=sz[x],val[tot]=val[x],rnd[tot]=rnd[x],sum[tot]=sum[x],rev[tot]=rev[x];return tot; }

inline void pushup(int o) { sz[o]=sz[ch[o][0]]+sz[ch[o][1]]+1,sum[o]=sum[ch[o][0]]+sum[ch[o][1]]+val[o]; }

void pushdown(int o)
{
    if(!rev[o]) return;
    if(ch[o][0]){
        ch[o][0]=nodecpy(ch[o][0]);
        rev[ch[o][0]]^=1,swap(ch[ch[o][0]][0],ch[ch[o][0]][1]);
    }
    if(ch[o][1]){
        ch[o][1]=nodecpy(ch[o][1]);
        rev[ch[o][1]]^=1,swap(ch[ch[o][1]][0],ch[ch[o][1]][1]);
    }
    rev[o]=0;
}

void split(int o,int k,int &x,int &y)
{
    if(!o) { x=y=0;return; }
    pushdown(o);
    if(k<=sz[ch[o][0]]){
        y=nodecpy(o);
        split(ch[y][0],k,x,ch[y][0]);pushup(y);
    }
    else{
        x=nodecpy(o);
        split(ch[x][1],k-sz[ch[o][0]]-1,ch[x][1],y);pushup(x);
    }
}

int merge(int x,int y)
{
    if(!x||!y) return x+y;
    if(rnd[x]<rnd[y]){
        pushdown(x);ch[x][1]=merge(ch[x][1],y);
        pushup(x);return x;
    }
    else{
        pushdown(y);ch[y][0]=merge(x,ch[y][0]);
        pushup(y);return y;
    }
}

inline int create(int v) { sz[++tot]=1,val[tot]=v,sum[tot]=v,rnd[tot]=rand();return tot; }

void ins(int &rt,int p,int v)
{
    int x,y;
    split(rt,p,x,y);
    rt=merge(merge(x,create(v)),y);
}

void del(int &rt,int p)
{
    int x,y,z;
    split(rt,p-1,x,y);split(y,1,y,z);
    rt=merge(x,z);
}

void flip(int &rt,int l,int r)
{
    int x,y,z;
    split(rt,l-1,x,y);split(y,r-l+1,y,z);
    rev[y]^=1,swap(ch[y][0],ch[y][1]);
    rt=merge(merge(x,y),z);
}

int query(int &rt,int l,int r)
{
    int x,y,z;
    split(rt,l-1,x,y);split(y,r-l+1,y,z);
    int res=sum[y];
    rt=merge(merge(x,y),z);
    return res;
}