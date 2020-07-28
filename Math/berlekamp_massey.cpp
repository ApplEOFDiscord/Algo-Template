#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int maxn=1e4+10;
const int mod=998244353;
LL a[maxn];

LL quickpow(LL a,LL x)
{
    LL res=1;
    while(x){
        if(x&1) res=res*a%mod;
        a=a*a%mod;
        x>>=1;
    }
    return res;
}

void bm(LL *a,int n,vector<LL> &coef)
{
    vector<LL> pre;
    int t=0;LL diff=0;
    for(int i=1;i<=n;i++){
        LL v=0;
        for(int j=0;j<coef.size();j++) v+=a[i-1-j]*coef[j],v%=mod;
        if((a[i]-v)%mod==0) continue;
        if(!t){
            t=i,diff=a[i]-v;
            for(int j=i;j;j--) coef.push_back(0);
            continue;
        }
        vector<LL> now=coef;
        LL r=(a[i]-v)*quickpow(diff,mod-2)%mod;
        if(coef.size()<pre.size()+i-t) coef.resize(pre.size()+i-t);
        coef[i-t-1]+=r,coef[i-t-1]%=mod;
        for(int j=0;j<pre.size();j++) coef[i-t+j]-=r*pre[j],coef[i-t+j]%=mod;
        if(now.size()-i<pre.size()-t) pre=now,t=i,diff=a[i]-v;
    }
    for(auto &x:coef) x=(x+mod)%mod;
}

LL calc(LL *a,LL n,vector<LL> &coef)
{
    int tot=coef.size();
    if(n<=tot) return a[n+1];
    static LL f[maxn],g[maxn],p[maxn],temp[maxn];
    p[0]=-1;
    for(int i=1;i<=tot;i++) p[i]=coef[i-1];
    for(int i=0;i<=(tot<<1);i++) f[i]=g[i]=0;
    f[0]=1;
    if(tot>1) g[1]=1;
    else g[0]=p[0];
    auto mul=[&](LL *a,LL *b,LL *c){
        for(int i=0;i<=(tot<<1);i++) temp[i]=0;
        for(int i=0;i<tot;i++)
            for(int j=0;j<tot;j++)
                temp[i+j]+=a[i]*b[j],temp[i+j]%=mod;
        for(int i=(tot<<1);i>=tot;i--)
            if(temp[i]%mod)
                for(int j=tot;~j;j--)
                    temp[i-j]+=temp[i]*p[j],temp[i-j]%=mod;
        for(int i=0;i<(tot<<1);i++) c[i]=temp[i];
        return 0;
    };
    while(n){
        if(n&1) mul(f,g,f);
        mul(g,g,g);
        n>>=1;
    }
    LL res=0;
    for(int i=0;i<tot;i++) res+=a[i+1]*f[i],res%=mod;
    return (res+mod)%mod;
}
