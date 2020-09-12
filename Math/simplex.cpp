#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int maxn=25;
const double eps=1e-8;

int n,m,t,id[maxn<<1];
double a[maxn][maxn],x[maxn];

int sgn(double x) {return x<-eps?-1:x>eps?1:0;}

void pivot(int r,int c)
{
    swap(id[n+r],id[c]);
    double temp;
    temp=a[r][c],a[r][c]=1;
    for(int j=0;j<=n;j++) a[r][j]/=temp;
    for(int i=0;i<=m;i++)
        if(i!=r&&sgn(a[i][c])){
            temp=a[i][c],a[i][c]=0;
            for(int j=0;j<=n;j++) a[i][j]-=a[r][j]*temp;
        }
}

bool init()
{
    while(1){
        int r=0,c=0;
        for(int i=1;i<=m;i++)
            if(sgn(a[i][0])<0&&(!r||rand()&1)) r=i;
        if(!r) break;
        for(int j=1;j<=n;j++)
            if(sgn(a[r][j])<0&&(!c||rand()&1)) c=j;
        if(!c){
            cout<<"Infeasible"<<endl;return 0;    //不存在满足所有约束的解
        }
        pivot(r,c);
    }
    return 1;
}

bool simplex()
{
    while(1){
        int r=0,c=0;double minv=DBL_MAX;
        for(int j=1;j<=n;j++)
            if(sgn(a[0][j])>0){
                c=j;break;
            }
        if(!c) break;
        for(int i=1;i<=m;i++)
            if(sgn(a[i][c])>0&&a[i][0]/a[i][c]<minv){
                minv=a[i][0]/a[i][c],r=i;
            }
        if(!r){
            cout<<"Unbounded"<<endl;return 0;      //目标函数值可以任意大
        }
        pivot(r,c);
    }
    return 1;
}