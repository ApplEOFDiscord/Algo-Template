#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int mod=998244353;
LL x[2010],y[2010];

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

LL lagrange(int n,LL *x,LL *y,LL v)
{
    LL res=0;
    for(int i=0;i<n;i++){
        LL nume=1,deno=1;
        for(int j=0;j<n;j++)
            if(i!=j){
                nume*=(v-x[j]),nume=(nume%mod+mod)%mod;    //分子分母各模两次，防止出现负数
                deno*=(x[i]-x[j]),deno=(deno%mod+mod)%mod;
            }
        res+=y[i]*nume%mod*quickpow(deno,mod-2)%mod,res%=mod;
    }
    return res;
}

/* 点值连续时，可以将复杂度优化到线性
LL pre[2010],suf[2010],inv[2010];

LL lagrange(int n,LL *x,LL *y,LL v)
{
    LL res=0;
    pre[0]=((v-x[0])%mod+mod)%mod,suf[n]=1;
    for(int i=1;i<n;i++) pre[i]=pre[i-1]*(v-x[i])%mod,pre[i]=(pre[i]+mod)%mod;
    for(int i=n-1;i>=0;i--) suf[i]=suf[i+1]*(v-x[i])%mod,suf[i]=(suf[i]+mod)%mod;
    inv[0]=inv[1]=1;
    for(int i=2;i<n;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for(int i=2;i<n;i++) inv[i]=inv[i]*inv[i-1]%mod;
    for(int i=0;i<n;i++) res+=y[i]*(i==0?1:pre[i-1])%mod*suf[i+1]%mod*inv[i]%mod*(((n-1-i)&1)?mod-1:1)%mod*inv[n-1-i]%mod,res%=mod;
    return res;
}*/

