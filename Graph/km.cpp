#include<bits/stdc++.h>
using namespace std;

const int maxn=500+10;
int n,match[maxn],pre[maxn];
LL g[maxn][maxn],lx[maxn],ly[maxn],slack[maxn];
bool visx[maxn],visy[maxn];

void bfs(int u)
{
  memset(pre,0,sizeof(pre));
  memset(slack,0x3f,sizeof(slack));
  int x,y=0,ny=0;
  match[y]=u;
  while(1){
    x=match[y],visy[y]=true;LL d=INF;
    for(int i=1;i<=n;i++){
      if(visy[i]) continue;
      if(lx[x]+ly[i]-g[x][i]<slack[i]) slack[i]=lx[x]+ly[i]-g[x][i],pre[i]=y;
      if(slack[i]<d) d=slack[i],ny=i;
    }
    for(int i=0;i<=n;i++){
      if(visy[i]) lx[match[i]]-=d,ly[i]+=d;
      else slack[i]-=d;
    }
    y=ny;
    if(match[y]==-1) break;
  }
  while(y) match[y]=match[pre[y]],y=pre[y];
}

LL km()
{
  memset(match,-1,sizeof(match));
  memset(lx,0,sizeof(lx));
  memset(ly,0,sizeof(ly));
  for(int i=1;i<=n;i++){
    memset(visy,0,sizeof(visy));
    bfs(i);
  }
  LL res=0;
  for(int i=1;i<=n;i++) res+=g[match[i]][i];
  return res;
}
