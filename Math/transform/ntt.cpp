#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod=998244353;
int rev[1000010],len,lim=1;

ll quickpow(ll a,ll x)
{
    //...
}

void init(int n)
{
    while(lim<n) lim<<=1,len++;
    for(int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
}

void ntt(ll *a,int flag)
{
    for(int i=0;i<lim;i++)
        if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(int i=2;i<=lim;i<<=1){
        ll gn=quickpow(3,(mod-1)/i);
        for(int j=0;j<lim;j+=i){
            ll t=1;
            for(int k=j;k<j+i/2;k++,t=t*gn%mod){
                ll op1=a[k],op2=t*a[k+i/2]%mod;
                a[k]=(op1+op2)%mod;
                a[k+i/2]=(op1-op2+mod)%mod;
            }
        }
    }
    if(flag==-1){
        reverse(a+1,a+lim);
        ll inv=quickpow(lim,mod-2);
        for(int i=0;i<lim;i++) a[i]=a[i]*inv%mod;
    }
}