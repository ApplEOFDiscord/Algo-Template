#include<bits/stdc++.h>
#define LL long long
using namespace std;

bool tag;
struct line{
  LL k,b;
  mutable function<const line*()> succ;
  bool operator<(const line &rhs) const{
    if(!tag) return k<rhs.k;
    const line* s=succ();
    if(!s) return 0;
    return 1.0L*b-s->b<1.0L*(s->k-k)*rhs.k;
  }
};

struct hull:public multiset<line>{
  bool bad(iterator y){
    auto z=next(y);
    if(y==begin()){
      if(z==end()) return 0;
      return y->k==z->k&&y->b<=z->b;
    }
    auto x=prev(y);
    if(z==end()) return y->k==x->k&&y->b<=x->b;
    return 1.0L*(x->b-y->b)*(z->k-y->k)>=1.0L*(y->b-z->b)*(y->k-x->k);
  }
  void add(LL k,LL b){
    auto y=insert({k,b});
    y->succ=[=]{return next(y)==end()?0:&*next(y);};
    if(bad(y)){ erase(y);return; }
    while(next(y)!=end()&&bad(next(y))) erase(next(y));
    while(y!=begin()&&bad(prev(y))) erase(prev(y));
  }
  LL eval(LL x){
    tag=true;line l=*lower_bound({x,0});tag=false;
    return l.k*x+l.b;
  }
};

/*
struct line
{
  LL k,b;
  LL eval(LL x){ return k*x+b; }
  LL intersect(line l){ return (long double)(b-l.b)/(l.k-k); }
};

deque<line> dq;
vector<int> id;

bool cmp(int i,LL x){ return dq[i].intersect(dq[i+1])<x; }

void init(int n)
{
  dq.push_front({0,0});
  id.resize(n+1);  
  iota(id.begin(),id.end(),0);
}

LL query(LL q)
{
  int p=*lower_bound(id.begin(),id.begin()+dq.size()-1,q,cmp);
  return dq[p].eval(q);
}

void add(line l)
{
  while(dq.size()>=2&&l.intersect(dq[0])>=dq[0].intersect(dq[1])) dq.pop_front();
  dq.push_front(l);
}
*/

