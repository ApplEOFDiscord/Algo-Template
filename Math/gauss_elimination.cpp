#include<bits/stdc++.h>
using namespace std;

const double eps=1e-8;
double a[2010][2010],x[2010];
bool pivot[2010];

int sgn(double x) {return x<-eps?-1:x>eps?1:0;}

//无解时返回-1,有解时返回自由变元数量(唯一解时等于0,无穷多解时大于0)
int gauss(int n,int m)
{
    int r=1,c=1;
    while(r<=n&&c<=m){
        int maxr=r;
        for(int i=r+1;i<=n;i++)
            if(fabs(a[i][c])>fabs(a[maxr][c])) maxr=i;
        if(maxr!=r)
            for(int j=c;j<=m+1;j++) swap(a[r][j],a[maxr][j]);
        if(!sgn(a[r][c])){
            a[r][c]=0,c++;continue;
        }
        
        for(int i=r+1;i<=n;i++)
            if(sgn(a[i][c])){ //a[i][c]非零时才进行相消，系数矩阵稀疏时能提升些速度
                //逆序枚举j避免使用中间变量(double t=a[i][c]/a[r][c];)带来的精度损失
                for(int j=m+1;j>=r;j--) a[i][j]-=a[i][c]/a[r][c]*a[r][j];
            }
        r++,c++;
    }
    for(int i=r;i<=n;i++)
        if(sgn(a[i][m+1])) return -1;
    for(int i=r-1;i>=1;i--){
        int pos;
        for(int j=1;j<=m;j++)
            if(sgn(a[i][j])){
                pivot[j]=true,pos=j;break;
            }
        double b=a[i][m+1];
        for(int j=m;j>pos;j--)
            if(pivot[j]) b-=a[i][j]*x[j];
        x[pos]=b/a[i][pos];   
    }
    return m-r+1;
}