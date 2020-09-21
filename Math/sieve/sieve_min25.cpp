#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int mod=1e9+7;
const int maxn=1e6+10;

int pri[maxn],sum[maxn],id1[maxn],id2[maxn],g[maxn],h[maxn],tot,blk,m;
LL n,w[maxn];
bool vis[maxn];

void sieve(int lim)
{
    for(int i=2;i<=lim;i++){
        if(!vis[i]) pri[++tot]=i,sum[tot]=(sum[tot-1]+i)%mod;
        for(int j=1;j<=tot&&i*pri[j]<=lim;j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0) break;
        }
    }
}

inline int id(LL x){ return (x<=blk)?id1[x]:id2[n/x]; }

void init()
{
    blk=sqrt(n);sieve(blk);
    for(LL l=1,r;l<=n;l=r+1){
        r=n/(n/l);w[++m]=n/l;
        if(w[m]<=blk) id1[w[m]]=m;
        else id2[n/w[m]]=m;
        g[m]=((w[m]+2)%mod)*((w[m]-1)%mod)%mod*((mod+1)/2)%mod;
        h[m]=(w[m]-1)%mod;
    }
    for(int j=1;j<=tot;j++)
        for(int i=1;i<=m&&1LL*pri[j]*pri[j]<=w[i];i++){
            int k=id(w[i]/pri[j]);
            g[i]=(g[i]-1LL*pri[j]*(g[k]-sum[j-1])%mod)%mod;g[i]=(g[i]+mod)%mod;
            h[i]=(h[i]-h[k]+j-1)%mod;h[i]=(h[i]+mod)%mod;
        }
}

int S(LL x,int y)
{
    if(x<=1||pri[y]>x) return 0;
    int k=id(x);
    int res=(g[k]-h[k]-sum[y-1]+y-1)%mod;res=(res+mod)%mod;
    if(y==1) res=(res+2)%mod;
    for(int i=y;i<=tot&&1LL*pri[i]*pri[i]<=x;i++){
        LL p=pri[i],q=1LL*pri[i]*pri[i];
        for(int e=1;q<=x;e++,p=q,q*=pri[i]) res=(res+1LL*S(x/p,i+1)*(pri[i]^e)%mod+(pri[i]^(e+1))%mod)%mod;
    }
    return res;
}
