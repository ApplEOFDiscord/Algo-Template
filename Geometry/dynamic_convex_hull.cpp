#include<bits/stdc++.h>
#define LL long long
using namespace std;

struct line
{
  LL k,b;
  LL eval(LL x){ return k*x+b; }
  LL intersect(line l){ return (long double)(b-l.b)/(l.k-k); }
};

deque<line> dq;
vector<int> id;

bool cmp(int i,int x){ return dq[i].intersect(dq[i+1])<x; }

void init(int n)
{
  dq.push_front({0,0});
  id.resize(n);  
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

