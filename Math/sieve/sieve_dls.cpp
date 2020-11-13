#include<bits/stdc++.h>
#define LL long long
using namespace std;

int pri[1000010],mu[100010],tot;
LL sum[1000010];
bool vis[1000010];
map<LL,LL> mp;

void sieve()
{
    mu[1]=1;
    for(int i=2;i<=1000000;i++){
        if(!vis[i]) pri[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot&&i*pri[j]<=1000000;j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0){
                mu[i*pri[j]]=0;break;
            }
            mu[i*pri[j]]=-mu[i];
        }
    }
    for(int i=1;i<=1000000;i++) sum[i]=sum[i-1]+mu[i];
}

LL get_mu(LL x)
{
    if(x<=1000000) return sum[x];
    if(mp[x]) return mp[x];
    LL res=1;
    for(LL l=2,r;l<=x;l=r+1){
        r=x/(x/l);
        res-=get_mu(x/l)*(r-l+1);
    }
    return mp[x]=res;
}

