#include<bits/stdc++.h>
#define LL long long
using namespace std;

int pri[5]={2,3,5,7,11};

LL quickmul(LL a,LL b,LL mod)
{
    LL res=0;
    while(b){
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}

LL quickpow(LL a,LL x,LL mod)
{
    LL res=1;
    while(x){
        if(x&1) res=quickmul(res,a,mod);
        a=quickmul(a,a,mod);
        x>>=1;
    }
    return res;
}

bool miller_rabin(LL x)
{
    if(x==2) return true;
    if(x<2||!(x&1)) return false;
    LL s=0,t=x-1;
    while(!(t&1)) s++,t>>=1;
    for(int i=0;i<5&&pri[i]<x;i++){
        LL pre=quickpow(pri[i],t,x);
        for(int j=1;j<=s;j++){
            LL now=quickmul(pre,pre,x);
            if(now==1&&pre!=1&&pre!=x-1) return false;
            pre=now;
        }
        if(pre!=1) return false; 
    }
    return true;
}