typedef long long ll;
ll fac[100010],inv[100010];

ll quickpow(ll a,ll x,ll p)
{
    ll res=1;
    while(x){
        if(x&1) res=(res*a)%p;
        a=(a*a)%p;
        x>>=1;
    }
    return res;
}

void init(int p)
{
    fac[0]=1;
    for(int i=1;i<=p-1;i++) fac[i]=fac[i-1]*i%p;
    inv[p-1]=quickpow(fac[p-1],p-2,p);
    for(int i=p-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%p;
}

ll C(ll n,ll m,ll p)
{
    if(n<m) return 0;
    return fac[n]*inv[m]%p*inv[n-m]%p;
}

ll lucas(ll n,ll m,ll p)
{
    if(!m) return 1;
    return (C(n%p,m%p,p)*lucas(n/p,m/p,p))%p;
}


