#include<bits/stdc++.h>
#define LL long long
using namespace std;

LL b[65],newb[65],cnt;
bool flag;

void insert(LL *b,LL x)
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

bool check(LL *b,LL x)
{
    for(int i=60;i>=0;i--)
        if(x&(1LL<<i)){
            if(!b[i]) return false;
            else x^=b[i];
        }
    return true;
}

LL query_max(LL *b)
{
    LL res=0;
    for(int i=60;i>=0;i--) res=max(res,res^b[i]);
    return res;
}

LL query_min(LL *b)
{
    if(flag) return 0; //可以异或出0
    for(int i=0;i<=60;i++)
        if(b[i]) return b[i];
    return 0;
}

//相当于把Gauss消元改为Gauss-Jordan消元,方便询问第k小
void rebuild(LL *b,LL *newb)
{
    for(int i=60;i>=0;i--){
        if(!b[i]) continue;
        for(int j=i+1;j<=60;j++)
            if(b[j]&(1LL<<i)) b[j]^=b[i];
    }
    for(int i=0;i<=60;i++)
        if(b[i]) newb[cnt++]=b[i];
}

LL query_kth(LL *newb,LL k)
{
    LL res=0;
    if(flag) k--;
    if(!k) return 0;
    if(k>=(1LL<<cnt)) return -1;
    for(int i=0;i<=60;i++)
        if(k&(1LL<<i)) res^=newb[i];
    return res;
}

LL all[65],mask[65];

//线性基求交
void intersect(LL *a,LL *b,LL *c)
{
    for(int i=0;i<32;i++) all[i]=a[i],mask[i]=(1LL<<i);
    for(int i=0;i<32;i++)
        if(b[i]){
            LL x=b[i],k=0;
            bool flag=true;
            for(int j=31;j>=0;j--)
                if(x&(1LL<<j)){
                    if(!all[j]){
                        all[j]=x,mask[j]=k;
                        flag=false;break;
                    }
                    x^=all[j],k^=mask[j];
                }
            if(flag){
                LL x=0;
                for(int j=0;j<32;j++)
                    if(k&(1LL<<j)) x^=a[j];
                insert(c,x);
            }
        }
}

