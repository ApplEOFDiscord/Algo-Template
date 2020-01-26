#include<bits/stdc++.h>
#define ls ch[x][0]
#define rs ch[x][1]
using namespace std;

const int maxn=1e5+10;
int ch[maxn][2],fa[maxn],sz[maxn],val[maxn],sum[maxn],rev[maxn],add[maxn],mul[maxn];

bool isroot(int x)
{
    return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
}

void pushup(int x)
{
    sz[x]=sz[ls]+sz[rs]+1;
    sum[x]=sum[ls]+sum[rs]+val[x];
}

void pushdown(int x)
{
    if(rev[x]){
        if(ls) rev[ls]^=1,swap(ch[ls][0],ch[ls][1]);
        if(rs) rev[rs]^=1,swap(ch[rs][0],ch[rs][1]);
    }
    if(!add[x]&&mul[x]==1) return;
    if(ls){
        add[ls]=add[ls]*mul[x]+add[x];
        mul[ls]=mul[ls]*mul[x];
        val[ls]=val[ls]*mul[x]+add[x];
        sum[ls]=sum[ls]*mul[x]+add[x]*sz[ls];
    }
    if(rs){
        add[rs]=add[rs]*mul[x]+add[x];
        mul[rs]=mul[rs]*mul[x];
        val[rs]=val[rs]*mul[x]+add[x];
        sum[rs]=sum[rs]*mul[x]+add[x]*sz[rs];
    }
    add[x]=0,mul[x]=1;
}

void update(int x)
{
    if(!isroot(x)) update(fa[x]);
    pushdown(x);
}

void rotate(int x)
{
    int y=fa[x],z=fa[y],d=ch[y][0]==x;
    fa[x]=z;
    if(!isroot(y)) ch[z][ch[z][1]==y]=x;
    ch[y][d^1]=ch[x][d];
    if(ch[x][d]) fa[ch[x][d]]=y;
    fa[y]=x,ch[x][d]=y;
    pushup(y),pushup(x);
}

void splay(int x)
{
    update(x);
    while(!isroot(x)){
        int y=fa[x],z=fa[y];
        if(!isroot(y)){
            int d=ch[z][0]==y;
            if(ch[y][d]==x) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}

void access(int x)
{
    int f=0;
    while(x){
        splay(x),ch[x][1]=f,pushup(x);
        f=x,x=fa[x];
    }
}

void makeroot(int x)
{
    access(x),splay(x);
    swap(ch[x][0],ch[x][1]);
    rev[x]^=1;
}

int findroot(int x)
{
    access(x),splay(x);
    while(ch[x][0]) pushdown(x),x=ch[x][0];
    splay(x);
    return x;
}

bool link(int x,int y)
{
    makeroot(x);
    if(findroot(y)==x) return 0;
    fa[x]=y;
    return 1;
}

bool cut(int x,int y)
{
    makeroot(x);
    if(findroot(y)!=x||fa[y]!=x||ch[y][0]) return 0;
    fa[y]=0,ch[x][1]=0;
}

void split(int x,int y)
{
    makeroot(x),access(y),splay(y);
}
