#include<bits/stdc++.h>
using namespace std;

const int maxn=5e5+10;

int last=1,tot=1;
int len[maxn<<1],fa[maxn<<1],ch[maxn<<1][26];
int sz[maxn<<1],c[maxn<<1],id[maxn<<1];

void add(int c)
{
    int p=last;int newp=last=++tot;
    len[newp]=len[p]+1,sz[newp]=1;
    while(p&&!ch[p][c]) ch[p][c]=newp,p=fa[p];
    if(!p) fa[newp]=1;
    else{
        int q=ch[p][c];
        if(len[q]==len[p]+1) fa[newp]=q;
        else{
            int newq=++tot;
            memcpy(ch[newq],ch[q],sizeof(ch[newq]));
            len[newq]=len[p]+1;
            fa[newq]=fa[q],fa[q]=fa[newp]=newq;
            while(p&&ch[p][c]==q) ch[p][c]=newq,p=fa[p];
        }
    }
}

void init()
{
    for(int i=1;i<=tot;i++) c[len[i]]++;
    for(int i=1;i<=tot;i++) c[i]+=c[i-1];
    for(int i=1;i<=tot;i++) id[c[len[i]]--]=i;
}