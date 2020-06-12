#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+10;
int f[maxn];
bool can[maxn];

void getfail(string &t)
{
    int m=t.size();
    f[0]=f[1]=0;
    for(int i=1;i<m;i++){
        int j=f[i];
        while(j&&t[i]!=t[j]) j=f[j];
        f[i+1]=(t[i]==t[j]?j+1:0);
    }
}

void kmp(string &s,string &t)
{
    int n=s.size(),m=t.size();
    getfail(t);
    int j=0;
    for(int i=0;i<n;i++){
        while(j&&s[i]!=t[j]) j=f[j];
        if(s[i]==t[j]) j++;
        if(j==m) can[i-m+1]=true;
    }
}
