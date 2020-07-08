#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int mod=1e9+7;
int n;

void fwt_or(LL *a,int flag)
{
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=j;k<j+i/2;k++)
                a[k+i/2]+=a[k]*flag,a[k+i/2]=(a[k+i/2]+mod)%mod;
}

void fwt_and(LL *a,int flag)
{
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=j;k<j+i/2;k++)
                a[k]+=a[k+i/2]*flag,a[k]=(a[k]+mod)%mod;
}

void fwt_xor(LL *a,int flag)
{
    LL inv2=(mod+1)/2;
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=j;k<j+i/2;k++){
               LL temp=a[k];
               if(flag==1){
                   a[k]+=a[k+i/2],a[k]%=mod;
                   a[k+i/2]-=temp,a[k+i/2]=(a[k+i/2]+mod)%mod;
               }
               else{
                   a[k]=(a[k]+a[k+i/2])*inv2%mod;
                   a[k+i/2]=(temp-a[k+i/2]+mod)*inv2%mod;
               }
            }
}