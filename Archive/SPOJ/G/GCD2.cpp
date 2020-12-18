// clang-format off
#include<algorithm>
// #include<cctype>
// #include<cmath>
#include<cstdio>
#include<cstring>
// #include<cstdint>
#include<vector>
using namespace std;
template<typename Q=int64_t>
struct BigInt{
inline void initCharArray(const char*s,int size=-1){_vs.clear();for(int i=(size>=0?size:strlen(s))-1;i>=0;i-=9){ int v=0;for(int j=min(i,8);j>=0;--j)v=v*10+s[i-j]-'0';_vs.push_back(v);}clean();}
inline void clean(){for(;_vs.size()>1&&!_vs.back();_vs.pop_back()){}}
inline Q operator%(Q v){Q mod=0;for(int i=static_cast<int>(_vs.size())-1;i>=0;--i){mod=(_vs[i]+mod*1000000000)%v;}return mod;}
vector<int>_vs;
};
int a,b;BigInt<>biB;char bs[256];
int main(){
int taskNumber;scanf("%d",&taskNumber);
for(int taskIdx=0;taskIdx<taskNumber;++taskIdx){scanf("%d%s",&a,bs);if(!a){puts(bs);continue;}biB.initCharArray(bs);b=biB%a;if(a<b)swap(a,b);for(;b;swap(a,b))a%=b;printf("%d\n",a);}
return 0;
}
// clang-format on
