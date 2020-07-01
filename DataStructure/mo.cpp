#include<bits/stdc++.h>
using namespace std;

const int maxn=50000+10;
int n,m,bel[maxn];

struct que
{
    int l,r,id;
    bool operator<(const que& rhs) const{
        if(bel[l]==bel[rhs.l]) return r<rhs.r;
        return bel[l]<bel[rhs.l];
    }
}q[maxn];

/* 奇偶优化，奇数块右端点从小到大排序，偶数块右端点从大到小排序，用于玄学卡常
struct que
{
    int l,r,id;
    bool operator<(const que& rhs) const{
        if(bel[l]==bel[rhs.l]){
            if(bel[l]&1) return r<rhs.r;
            else return r>rhs.r;
        }
        return bel[l]<bel[rhs.l];
    }
}q[maxn];*/

void add(int x)
{
    //...
}

void del(int x)
{
    //...
}

void solve()
{
    int blk=sqrt(n);
    for(int i=1;i<=n;i++) bel[i]=(i-1)/blk+1;
    //...
    sort(q+1,q+m+1);
    int L=1,R=0;
    for(int i=1;i<=m;i++){
        while(L<q[i].l) del(L++);
        while(L>q[i].l) add(--L);
        while(R<q[i].r) add(++R);
        while(R>q[i].r) del(R--);
        //...
    }
}