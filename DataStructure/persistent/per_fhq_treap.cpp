#include<bits/stdc++.h>
using namespace std;

const int maxn=5e5+10;
const int INF=2147483647;
int rt[maxn],ch[maxn*40][2],val[maxn*40],rnd[maxn*40],sz[maxn*40],tot,x,y,z;

inline int nodecpy(int x) { ch[++tot][0]=ch[x][0],ch[tot][1]=ch[x][1],sz[tot]=sz[x],val[tot]=val[x],rnd[tot]=rnd[x];return tot; }

inline void pushup(int o) { sz[o]=sz[ch[o][0]]+sz[ch[o][1]]+1; }

void split(int o,int v,int &x,int &y)
{
    if(!o) { x=y=0;return; }
    if(v<val[o]){
        y=nodecpy(o);
        split(ch[y][0],v,x,ch[y][0]);pushup(y);
    }
    else{
        x=nodecpy(o);
        split(ch[x][1],v,ch[x][1],y);pushup(x);
    }
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

void ins(int &rt,int v)
{
    split(rt,v,x,y);
    rt=merge(merge(x,create(v)),y);
}

void del(int &rt,int v)
{
    split(rt,v-1,x,y);split(y,v,y,z);
    y=merge(ch[y][0],ch[y][1]);
    rt=merge(merge(x,y),z);
}

int rnk(int &rt,int v)
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

int pre(int &rt,int v)
{
    split(rt,v-1,x,y);
    if(!x) return -INF;
    int res=kth(x,sz[x]);
    rt=merge(x,y);
    return res;
}

int nxt(int &rt,int v)
{
    split(rt,v,x,y);
    if(!y) return INF;
    int res=kth(y,1);
    rt=merge(x,y);
    return res;
}