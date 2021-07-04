#include<bits/stdc++.h>
#define LL long long
#define ls o<<1
#define rs o<<1|1
using namespace std;

const int maxn=1e6+10;
int a[maxn],mx[maxn<<2],se[maxn<<2],cnt[maxn<<2],tag[maxn<<2];
LL sum[maxn<<2];

void pushup(int o)
{
  sum[o]=sum[ls]+sum[rs];
  if(mx[ls]==mx[rs]){
    mx[o]=mx[ls];
    cnt[o]=cnt[ls]+cnt[rs];
    se[o]=max(se[ls],se[rs]);
  }
  else if(mx[ls]>mx[rs]){
    mx[o]=mx[ls];
    cnt[o]=cnt[ls];
    se[o]=max(se[ls],mx[rs]);
  }
  else{
    mx[o]=mx[rs];
    cnt[o]=cnt[rs];
    se[o]=max(mx[ls],se[rs]);
  }
}

void build(int o,int l,int r)
{
  tag[o]=-1;
  if(l==r){
    mx[o]=sum[o]=a[l],se[o]=-1,cnt[o]=1;
    return;
  }
  int mid=(l+r)>>1;
  build(ls,l,mid),build(rs,mid+1,r);
  pushup(o);
}

void pushdown(int o)
{
  if(tag[o]==-1) return;
  if(mx[ls]>tag[o]){
    sum[ls]-=1LL*cnt[ls]*(mx[ls]-tag[o]);
    mx[ls]=tag[ls]=tag[o];
  }
  if(mx[rs]>tag[o]){
    sum[rs]-=1LL*cnt[rs]*(mx[rs]-tag[o]);
    mx[rs]=tag[rs]=tag[o];
  }
  tag[o]=-1;
}

void update(int o,int l,int r,int ll,int rr,int v)
{
  if(v>=mx[o]) return;
  if(ll<=l&&r<=rr&&v>se[o]){
    sum[o]-=1LL*cnt[o]*(mx[o]-v);
    mx[o]=tag[o]=v;
    return;
  }
  pushdown(o);
  int mid=(l+r)>>1;
  if(ll<=mid) update(ls,l,mid,ll,rr,v);
  if(rr>mid) update(rs,mid+1,r,ll,rr,v);
  pushup(o);
}

int query_max(int o,int l,int r,int ll,int rr)
{
  if(ll<=l&&r<=rr) return mx[o];
  pushdown(o);
  int mid=(l+r)>>1,res=-1;
  if(ll<=mid) res=max(res,query_max(ls,l,mid,ll,rr));
  if(rr>mid) res=max(res,query_max(rs,mid+1,r,ll,rr));
  return res;
}

LL query_sum(int o,int l,int r,int ll,int rr)
{
  if(ll<=l&&r<=rr) return sum[o];
  pushdown(o);
  int mid=(l+r)>>1;LL res=0;
  if(ll<=mid) res+=query_sum(ls,l,mid,ll,rr);
  if(rr>mid) res+=query_sum(rs,mid+1,r,ll,rr);
  return res;
}