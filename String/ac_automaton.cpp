#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+10;
int ch[maxn][26],f[maxn],ed[maxn],tot;
queue<int> q;

void insert(string &s)
{
    int n=s.size(),o=0;
    for(int i=0;i<n;i++){
        int c=s[i]-'a';
        if(!ch[o][c]) ch[o][c]=++tot;
        o=ch[o][c];
    }
    ed[o]++;
}

void build()
{
    for(int c=0;c<26;c++)
        if(ch[0][c]) q.push(ch[0][c]);
    while(!q.empty()){
        int o=q.front();q.pop();
        for(int c=0;c<26;c++){
            if(ch[o][c]) f[ch[o][c]]=ch[f[o]][c],q.push(ch[o][c]);
            else ch[o][c]=ch[f[o]][c];
        }
    }
}

int query(string &s)
{
    int res=0,n=s.size(),o=0;
    for(int i=0;i<n;i++){
        o=ch[o][s[i]-'a'];
        for(int j=o;j&&ed[j]!=-1;j=f[j]) res+=ed[j],ed[j]=-1;
    }
    return res;
}