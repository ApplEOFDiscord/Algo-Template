typedef long long ll;
int pri[1000010],powv[1000010],powt[1000010],f[1000010],tot; //powt是最小素因子的次数,powv是最小素因子的次幂,f是要线筛的积性函数
bool vis[1000010];

void sieve()
{
    /* f[1]=...; 将f[1]赋值为f(1) */
    for(int i=2;i<=1000000;i++){
        if(!vis[i]){
            pri[++tot]=powv[i]=i,powt[i]=1;
            /* f[i]=...; i为素数,直接求出f(i) */
        }
        for(int j=1;j<=tot&&i*pri[j]<=1000000;j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0){
                powv[i*pri[j]]=powv[i]*pri[j],powt[i*pri[j]]=powt[i]+1;
                if(powv[i]==i){
                    /* f[i*pri[j]]=...; i为素数次幂,用f(p^k)的关系递推 */
                }
                else f[i*pri[j]]=f[i/powv[i]]*f[powv[i]*pri[j]];
                break;
            }
            powv[i*pri[j]]=pri[j],powt[i*pri[j]]=1;
            f[i*pri[j]]=f[i]*f[pri[j]];
        }
    }
}