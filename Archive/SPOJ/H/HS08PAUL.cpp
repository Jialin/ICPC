// clang-format off
#include<algorithm>
#include<cctype>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
constexpr int RB=1<<15;
char readBuffer[RB];
int readPos,readLength;
bool ended=false;
inline void loadBuffer(){readLength=static_cast<int>(fread(readBuffer,sizeof(char),RB,stdin));readPos=0;}
inline char readChar(bool advance=true){if(ended)return 0;if(readPos>=readLength){loadBuffer();if(readLength==0){ended=true;return 0;}}return readBuffer[advance?readPos++:readPos];}
template<typename T>inline bool readInt(T&res){char ch;while(true){ch=readChar(false);if(!ch)return false;if(!isspace(ch))break;++readPos;}ch=readChar(false);bool negative=ch=='-';if(negative)++readPos;res=0;while(true){ch=readChar(false);if(!isdigit(ch))break;res=res*10+(ch-'0');++readPos;}if(negative)res=-res;return true;}
constexpr int WB=1<<15;
static int writePos=0;
static char writeBuffer[WB];
inline void writeChar(char x){if(writePos==WB){fwrite(writeBuffer,1,WB,stdout);writePos=0;}writeBuffer[writePos++]=x;}
struct Flusher{inline~Flusher(){if(writePos){fwrite(writeBuffer,1,writePos,stdout);writePos=0;}}}flusher;
template<class T>inline void writeInt(T x){static char s[32];if(x<0){writeChar('-');x=-x;}int n=0;for(;x||!n;x/=10)s[n++]='0'+x%10;for(;n>0;writeChar(s[--n])){}}
const int PL=2*3*5*7,CC=48,CO[CC]={1,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,121,127,131,137,139,143,149,151,157,163,167,169,173,179,181,187,191,193,197,199,209};
class PrimeChecker{
public:
inline PrimeChecker(int n=30){
precompute_();
init(n);
}
inline void init(int n){
int size=n/PL+1;
sieve_.assign(size,0);
sieve_[0]=1;
int bound=static_cast<int>(sqrt(n)+1);
memcpy(mul_,mulInit_,sizeof(mul_));
auto*sieve=sieve_.data();
const auto*sieveEnd=sieve+size;
for(int base=0;base<=bound;base+=PL,++sieve){
for(int i=0;i<CC;++i){
if(!((*sieve>>i)&1)){
int v=base+CO[i],vv=v*v;
tag_(
cI[vv%PL],
sieve_.data()+vv/PL,
sieveEnd,
mul_[i],
nextIdx_[i]);
}
for(int k=0;k<CC;++k){
mul_[i][k]+=mulStep_[i][k];
}
}
}
}
inline bool isPrime(int x){
if(x==2||x==3||x==5||x==7){
return true;
}
int idx=cI[x%PL];
return idx>=0&&!((sieve_[x/PL]>>idx)&1);
}
inline void precompute_(){
memset(cI,0xFF,sizeof(cI));
for(int i=0;i<CC;++i){
cI[CO[i]]=i;
}
for(int i=0;i<CC;++i){
for(int j=0;j<CC;++j){
int sum=CO[i]+CO[j],step=1,delta=0;
if(sum>=PL){
sum-=PL;
++delta;
}
for(;cI[sum]<0;++step){
sum+=CO[i];
if(sum>=PL){
sum-=PL;
++delta;
}
}
nextIdx_[i][j]=cI[sum];
mulInit_[i][j]=delta;
mulStep_[i][j]=step;
}
}
}
inline void tag_(
int idx,
long long*sieve,
const long long*sieveEnd,
const int*mul,
const int*nextIdx){
while(sieve<sieveEnd){
*sieve|=1LL<<idx;
sieve+=mul[idx];
idx=nextIdx[idx];
}
}
int mul_[CC][CC];
int cI[PL];
int mulInit_[CC][CC];
int mulStep_[CC][CC];
int nextIdx_[CC][CC];
vector<long long>sieve_;
};
struct Query{
int v,idx,answer;
inline Query(int idx_){
idx=idx_;
readInt(v);
}
};
vector<Query>queries;
vector<int>isValid;
int main(){
int taskNumber;
readInt(taskNumber);
queries.reserve(taskNumber);
for(int taskIdx=1;taskIdx<=taskNumber;++taskIdx)
queries.push_back(Query(taskIdx));
sort(queries.begin(),queries.end(),[](const auto&lhs,const auto&rhs){
return lhs.v<rhs.v;
});
int bound=queries.back().v;
PrimeChecker pc(bound);
isValid.assign((bound+1)>>1,false);
int yyBound=static_cast<int>(sqrt(bound)+1);
for(int yy=0,dy=1;;dy+=2){
yy+=dy;
if(yy>yyBound)
break;
int v=yy*yy;
for(int dx=1;;dx+=2){
v+=dx;
if(v>bound)
break;
if((v&1)&&pc.isPrime(v)){
isValid[v>>1]=true;
}
}
}
int lastV=0,cnt=0;
for(auto&query:queries){
for(;lastV<=query.v;++lastV){
if(lastV==2||((lastV&1)&&isValid[lastV>>1]))
++cnt;
}
query.answer=cnt;
}
sort(queries.begin(),queries.end(),[](const auto&lhs,const auto&rhs){
return lhs.idx<rhs.idx;
});
for(const auto&query:queries){
writeInt(query.answer);
    writeChar('\n');
}
return 0;
}
