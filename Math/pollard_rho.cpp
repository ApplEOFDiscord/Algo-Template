#include<bits/stdc++.h>
#define LL long long
using namespace std;

LL test[7]={2,325,9375,28178,450775,9780504,1795265022};

/*
LL quickmul(LL a,LL b,LL mod)
{
    LL res=0;
    while(b){
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}*/

inline LL quickmul(LL a,LL b,LL mod)
{
    return (a*b-(LL)((long double)a*b/mod+1e-9)*mod)%mod;
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
    for(int i=0;i<7&&test[i]<x;i++){
        LL pre=quickpow(test[i],t,x);
        for(int j=1;j<=s;j++){
            LL now=quickmul(pre,pre,x);
            if(now==1&&pre!=1&&pre!=x-1) return false;
            pre=now;
        }
        if(pre!=1) return false; 
    }
    return true;
}

LL gcd(LL a,LL b)
{
    if(!b) return a;
    return gcd(b,a%b);
}

inline LL f(LL x,LL c,LL n)
{
    return (quickmul(x,x,n)+c)%n;
}

mt19937 mt(time(0));

inline LL get_rand(LL x,LL y)
{
    return uniform_int_distribution<LL>(x,y)(mt);
}

LL pollard_rho(LL x)
{
    if(x==4) return 2;
    LL p=get_rand(1,x-1),q=p,c=get_rand(1,x-1);
    p=f(p,c,x),q=f(f(q,c,x),c,x);
    for(int lim=1;p!=q;lim=min(128,lim<<1)){
        LL now=1;
        for(int i=0;i<lim;i++){
            LL temp=quickmul(now,abs(q-p),x);
            if(!temp) break;
            now=temp;
            p=f(p,c,x),q=f(f(q,c,x),c,x);
        }
        LL d=gcd(now,x);
        if(d>1) return d;
    }
    return x;
}

vector<LL> fac;

void get_fac(LL x)
{
    if(x==1) return;
    if(miller_rabin(x)){
        fac.push_back(x);return;
    }
    LL p=x;
    while(p>=x) p=pollard_rho(x);
    get_fac(p),get_fac(x/p);
}
