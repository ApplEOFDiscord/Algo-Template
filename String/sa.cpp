#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+10;
int sa[maxn],x[maxn],y[maxn],cnt[maxn];

void get_sa(string &s,int m)
{
    int n=s.size();
    for(int i=0;i<n;i++) cnt[x[i]=s[i]]++;
    partial_sum(cnt,cnt+m,cnt);
    for(int i=n-1;i>=0;i--) sa[--cnt[x[i]]]=i;
    for(int k=1;k<=n;k<<=1){
        int p=0;
        for(int i=n-k;i<n;i++) y[p++]=i;
        for(int i=0;i<n;i++)
            if(sa[i]>=k) y[p++]=sa[i]-k;
        memset(cnt,0,sizeof(cnt));
        for(int i=0;i<n;i++) cnt[x[y[i]]]++;
        partial_sum(cnt,cnt+m,cnt);
        for(int i=n-1;i>=0;i--) sa[--cnt[x[y[i]]]]=y[i];
        swap(x,y);
        p=1,x[sa[0]]=0;
        for(int i=1;i<n;i++)
            x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
        if(p>=n) break;
        m=p;
    }
}