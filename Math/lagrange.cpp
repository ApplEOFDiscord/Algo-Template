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