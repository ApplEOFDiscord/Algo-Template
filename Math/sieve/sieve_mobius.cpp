int pri[1000010],mu[1000010],tot;
bool vis[1000010];

void sieve()
{
    mu[1]=1;
    for(int i=2;i<=1000000;i++){
        if(!vis[i]) pri[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot&&i*pri[j]<=1000000;j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0){
                mu[i*pri[j]]=0;break;
            }
            mu[i*pri[j]]=-mu[i];
        }
    }
}