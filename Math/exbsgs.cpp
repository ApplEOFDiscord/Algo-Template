#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int mod=1e9+7;
unordered_map<LL,int> mp;

LL gcd(LL a,LL b)
{
    if(!b) return a;
    return gcd(b,a%b);
}

LL quickpow(LL a,LL x,LL mod)
{
    LL res=1;
    while(x){
        if(x&1) res=res*a%mod;
        a=a*a%mod;
        x>>=1;
    }
    return res;
}

LL exgcd(LL a,LL b,LL &x,LL &y)
{
    if(!b){
        x=1,y=0;return a;
    }
    LL res=exgcd(b,a%b,y,x);
    y-=x*(a/b);
    return res;
}

LL bsgs(LL a,LL b,LL mod)
{
    mp.clear();
    LL blk=ceil(sqrt(mod)),now=b%mod;
    for(int i=1;i<=blk;i++) now=now*a%mod,mp[now]=i;
    LL temp=quickpow(a,blk,mod);
    now=1;
    for(int i=1;i<=blk;i++){
        now=now*temp%mod;
        if(mp[now]) return (i*blk-mp[now]+mod)%mod; 
    }
    return -1;
}

LL exbsgs(LL a,LL b,LL mod)
{
    if(b==1||mod==1) return 0;
    LL g=gcd(a,mod),k=0,now=1;
    while(g>1){
        if(b%g!=0) return -1;
        k++,b/=g,mod/=g,now=now*(a/g)%mod;
        if(now==b) return k;
        g=gcd(a,mod);
    }
    LL x,y;
    exgcd(now,mod,x,y);
    x=(x%mod+mod)%mod;
    LL res=bsgs(a,b*x%mod,mod);
    if(res==-1) return -1;
    return res+k;
}