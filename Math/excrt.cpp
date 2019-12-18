typedef long long ll;

ll mul(ll a,ll b,ll mod)
{
    ll res=0;
    while(b){
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b){
        x=1,y=0;return a;
    }
    ll res=exgcd(b,a%b,y,x);
    y-=x*(a/b);
    return res;
}

ll excrt(ll *r,ll *m,int n)
{
    ll x,y,g,R=r[1],M=m[1];
    for(int i=2;i<=n;i++){
        g=exgcd(M,m[i],x,y);
        ll d=((r[i]-R)%m[i]+m[i])%m[i];
        if(d%g) return -1;
        x=mul(x,d/g,m[i]/g); //防止爆long long
        R+=M*x;
        M*=m[i]/g;
        R=(R%M+M)%M;
    }
    return R;
}