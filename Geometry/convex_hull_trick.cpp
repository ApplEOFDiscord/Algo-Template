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
void init()
{
  dq.push_front(line{0,0});
}

LL query(LL q)
{
  while(dq.size()>=2&&dq.back().eval(q)<=dq[dq.size()-2].eval(q)) dq.pop_back();
  return dq.back().eval(q);
}

void add(line l)
{
  while(dq.size()>=2&&l.intersect(dq[0])>=dq[0].intersect(dq[1])) dq.pop_front();
  dq.push_front(l);
}
