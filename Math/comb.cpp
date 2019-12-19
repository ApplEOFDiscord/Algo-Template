#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD=1e9+7;
ll fac[100010],inv[100010],c[3010][3010];

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    //...
}

//n*m较大时使用,必要时结合lucas定理
void init_fac(ll mod)
{
    int lim=min(100000LL,mod-1); //mod较小时,阶乘处理到mod-1即可(后面都是0)
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=fac[i-1]*i%mod;
    ll x,y;exgcd(fac[lim],mod,x,y);x=(x%mod+mod)%mod; //mod不一定为素数,exgcd求逆元
    inv[lim]=x;
    for(int i=lim-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}

ll C(ll n,ll m,ll mod)
{
    if(n<m) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

//n*m较小时可以使用
void init_c(int n)
{
    c[1][0]=c[1][1]=1;
    for(int i=2;i<=n;i++){
        c[i][0]=1;
        for(int j=1;j<=i;j++)
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
    }
}