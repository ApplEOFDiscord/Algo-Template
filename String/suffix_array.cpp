#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+10;
char s[maxn];
int sa[maxn],x[maxn],y[maxn],cnt[maxn];
int h[maxn],rk[maxn];

void get_sa(int m)
{
  int n=strlen(s+1);
  memset(cnt,0,sizeof(cnt));
  for(int i=1;i<=n;i++) cnt[x[i]=s[i]]++;
  partial_sum(cnt+1,cnt+m+1,cnt+1);
  for(int i=n;i>=1;i--) sa[cnt[x[i]]--]=i;
  for(int k=1;k<=n;k<<=1){
    int p=0;
    for(int i=n-k+1;i<=n;i++) y[++p]=i;
    for(int i=1;i<=n;i++)
      if(sa[i]>k) y[++p]=sa[i]-k;
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++) cnt[x[y[i]]]++;
    partial_sum(cnt+1,cnt+m+1,cnt+1);
    for(int i=n;i>=1;i--) sa[cnt[x[y[i]]]--]=y[i];
    swap(x,y);
    p=1,x[sa[1]]=1;
    for(int i=2;i<=n;i++)
      x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p:++p;
    if(p>=n) break;
    m=p;
  }
}

void get_height()
{
  int n=strlen(s+1);
  for(int i=1;i<=n;i++) rk[sa[i]]=i;
  int k=0;
  for(int i=1;i<=n;i++){
    if(rk[i]==1) continue;
    if(k) k--;
    int j=sa[rk[i]-1];
    while(s[i+k]==s[j+k]) k++;
    h[rk[i]]=k;
  }
}
