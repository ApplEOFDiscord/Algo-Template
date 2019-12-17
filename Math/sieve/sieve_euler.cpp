int pri[1000010],phi[1000010],tot;
bool vis[1000010];

void sieve()
{
    phi[1]=1;
    for(int i=2;i<=1000000;i++){
        if(!vis[i]) pri[++tot]=i,phi[i]=i-1;
        for(int j=1;j<=tot&&i*pri[j]<=1000000;j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0){
                phi[i*pri[j]]=phi[i]*pri[j];break;
            }
            phi[i*pri[j]]=phi[i]*(pri[j]-1);
        }
    }
}