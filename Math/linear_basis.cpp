#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll b[65],newb[65],cnt;
bool flag;

void insert(ll x)
{
    for(int i=60;i>=0;i--)
        if(x&(1LL<<i)){
            if(!b[i]){
                b[i]=x;return;
            }
            x^=b[i];
        }
    flag=true;
}

bool check(ll x)
{
    for(int i=60;i>=0;i--)
        if(x&(1LL<<i)){
            if(!b[i]) return false;
            else x^=b[i];
        }
    return true;
}

ll query_max()
{
    ll res=0;
    for(int i=60;i>=0;i--) res=max(res,res^b[i]);
    return res;
}

ll query_min()
{
    if(flag) return 0; //可以异或出0
    for(int i=0;i<=60;i++)
        if(b[i]) return b[i];
    return 0;
}

//相当于把Gauss消元改为Gauss-Jordan消元,方便询问第k小
void rebuild()
{
    for(int i=60;i>=0;i--){
        if(!b[i]) continue;
        for(int j=i+1;j<=60;j++)
            if(b[j]&(1LL<<i)) b[j]^=b[i];
    }
    for(int i=0;i<=60;i++)
        if(b[i]) newb[cnt++]=b[i];
}

ll query_kth(ll k)
{
    ll res=0;
    if(flag) k--;
    if(!k) return 0;
    if(k>=(1LL<<cnt)) return -1;
    for(int i=0;i<=60;i++)
        if(k&(1LL<<i)) res^=newb[i];
    return res;
}

