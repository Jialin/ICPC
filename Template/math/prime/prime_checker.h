#pragma once

#include <cmath>
#include <vector>
using namespace std;

// clang-format off
namespace math {

namespace {

const int PRIME_BITS[8]={1,7,11,13,17,19,23,29};
const int PRIME_INV[30]={-1,0,-1,-1,-1,-1,-1,1,-1,-1,-1,2,-1,3,-1,-1,-1,4,-1,5,-1,-1,-1,6,-1,-1,-1,-1,-1,7};

} // namespace

class PrimeChecker {
public:
  inline PrimeChecker(int n=30) {
    init(n);
  }

  #define DO(P,R,I,M,E,S,i0,v0,i1,v1,i2,v2,i3,v3,i4,v4,i5,v5,i6,v6,i7,v7) k=P;if(!(sieve[n]&(1<<R))){e=eos-I*n-M;\
  for(m=sieve+(30*n+E)*n+S;m<e;m+=i0){*m|=1<<v0;*(m+=i1)|=1<<v1;*(m+=i2)|=1<<v2;*(m+=i3)|=1<<v3;*(m+=i4)|=1<<v4;*(m+=i5)|=1<<v5;*(m+=i6)|=1<<v6;*(m+=i7)|=1<<v7;}\
  if(m<eos){*m|=1<<v0;if((m+=i1)<eos){*m|=1<<v1;if((m+=i2)<eos){*m|=1<<v2;if((m+=i3)<eos){*m|=1<<v3;if((m+=i4)<eos){*m|=1<<v4;if((m+=i5)<eos){*m|=1<<v5;if((m+=i6)<eos)*m|=1<<v6;}}}}}}}

  inline void init(int n_) {
    int bytes=n_/30+1;
    sieve_.assign(bytes,0);
    int p,q,r,k=0,n,s;
    char*m,*e,*eos,*sieve=sieve_.data();
    if(bytes>30)for(k=r=(bytes-1)/30;(q=r/k)<k;k>>=1)k+=q;
    eos=sieve+bytes;s=k+1;*sieve=1;
    for(n=p=q=r=0;n<s;++n){
      DO(p++,0,28,0,2,0,p,0,r,1,q,2,k,3,q,4,k,5,q,6,r,7);r++;
      DO(q++,1,24,6,14,1,r,5,q,4,p,0,k,7,p,3,q,2,r,6,p,1);r++;q++;
      DO(p-1,2,26,9,22,4,q,0,k,6,q,1,k,7,q,3,r,5,p,2,r,4);r++;
      DO(q-1,3,28,12,26,5,p,5,q,2,p,1,k,7,r,4,p,3,r,0,k,6);
      DO(q+1,4,26,15,34,9,q,5,p,6,k,0,r,3,p,4,r,7,k,1,p,2);r++;
      DO(p+1,5,28,17,38,12,k,0,q,4,r,2,p,5,r,3,q,7,k,1,q,6);r++;q++;
      DO(q++,6,26,20,46,17,k,5,r,1,p,6,r,2,k,3,p,7,q,0,p,4);r++;
      DO(p++,7,24,23,58,28,r,0,k,7,r,6,q,5,p,4,q,3,p,2,q,1);
    }
  }

  inline bool isPrime(int x) {
    if (x==2||x==3||x==5)return true;
    int idx=PRIME_INV[x%30];
    return idx >= 0 && !(sieve_[x/30]&(1<<idx));
  }

private:
  vector<char> sieve_;
};

} // namespace math
// clang-format on
