#include<bits/stdc++.h>
#define PI acos(-1.0)
using namespace std;

int rev[1000010],len,lim=1;

struct cp
{
    double x,y;
    cp(){x=0,y=0;}
    cp(double a,double b):x(a),y(b){}
    cp operator+(const cp &rhs) const
    {
        return cp(x+rhs.x,y+rhs.y);
    }
    cp operator-(const cp &rhs) const
    {
        return cp(x-rhs.x,y-rhs.y);
    }
    cp operator*(const cp &rhs) const
    {
        return cp(x*rhs.x-y*rhs.y,x*rhs.y+y*rhs.x);
    }
};

//长度补成2的次幂，并把系数重新排列(将原位置的二进制位反转后得到当前位置)
void init(int n)
{
    while(lim<n) lim<<=1,len++;
    for(int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
}

//flag等于１时做DFT,flag等于-1时做IDFT
void fft(cp *a,int flag)
{
    for(int i=0;i<lim;i++)
        if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(int i=2;i<=lim;i<<=1){
        cp wn(cos(2*PI/i),flag*sin(2*PI/i));
        for(int j=0;j<lim;j+=i){
            cp t(1,0);
            for(int k=j;k<j+i/2;k++,t=t*wn){
                cp op1=a[k],op2=t*a[k+i/2];
                a[k]=op1+op2;
                a[k+i/2]=op1-op2;
            }
        }
    }
    if(flag==-1){
        for(int i=0;i<lim;i++) a[i].x/=lim;   //后面处理系数时注意精度损失(...=(int)(a[i].x+0.5))
    }
}