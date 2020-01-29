const int maxn=1e5+10;
int rt[maxn],lcur[maxn],rcur[maxn],ls[maxn*200],rs[maxn*200],sum[maxn*200],n,tot;

void update(int &o,int l,int r,int pos,int v)
{
    if(!o) o=++tot;
    sum[o]+=v;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) update(ls[o],l,mid,pos,v);
    else update(rs[o],mid+1,r,pos,v);
}

inline int lowbit(int o) { return o&(-o); }

void updateall(int o,int pos,int v)
{
    for(;o<=n;o+=lowbit(o)) update(rt[o],1,n,pos,v);
}

void getroot(int ll,int rr)
{
    for(int o=rr;o;o-=lowbit(o)) rcur[o]=rt[o];
    for(int o=ll-1;o;o-=lowbit(o)) lcur[o]=rt[o];
}

int kth(int l,int r,int ll,int rr,int k)
{
    if(l==r) return l;
    int mid=(l+r)>>1,cnt=0;
    for(int o=rr;o;o-=lowbit(o)) cnt+=sum[ls[rcur[o]]];
    for(int o=ll-1;o;o-=lowbit(o)) cnt-=sum[ls[lcur[o]]];
    if(cnt>=k){
        for(int o=rr;o;o-=lowbit(o)) rcur[o]=ls[rcur[o]];
        for(int o=ll-1;o;o-=lowbit(o)) lcur[o]=ls[lcur[o]];
        return kth(l,mid,ll,rr,k);
    }
    else{
        for(int o=rr;o;o-=lowbit(o)) rcur[o]=rs[rcur[o]];
        for(int o=ll-1;o;o-=lowbit(o)) lcur[o]=rs[lcur[o]];
        return kth(mid+1,r,ll,rr,k-cnt);
    }
}