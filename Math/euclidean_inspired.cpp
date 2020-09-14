#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int mod=998244353;
const int inv2=(mod+1)/2;

//注意爆long long的问题(多模几次/换int128)
LL f(LL a,LL b,LL c,LL n)
{
    if(!a) return (n+1)*(b/c)%mod;
    if(a>=c||b>=c) return ((a/c)*n%mod*(n+1)%mod*inv2%mod+(b/c)*(n+1)%mod+f(a%c,b%c,c,n))%mod;
    LL m=(a*n+b)/c;
    return (n*m%mod-f(c,c-b-1,a,m-1)+mod)%mod;
}
