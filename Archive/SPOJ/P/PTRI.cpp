// clang-format off
#include<algorithm>
#include<cctype>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<functional>
#include<vector>
using namespace std;
constexpr int kReadBufferSize=1<<15;char readBuffer[kReadBufferSize];int readPos,readLength;bool ended=false;
inline void loadBuffer(){readLength=static_cast<int>(fread(readBuffer,sizeof(char),kReadBufferSize,stdin));readPos=0;}
inline char readChar(bool advance=true){if(ended)return 0;if(readPos>=readLength){loadBuffer();if(!readLength){ended=true;return 0;}}return readBuffer[advance?readPos++:readPos];}
inline bool readInt(int& res){char ch;while(true){ch=readChar(false);if(!ch)return false;if(!isspace(ch))break;++readPos;}ch=readChar(false);bool negative=ch=='-';if(negative){++readPos;}res=0;while(true){ch=readChar(false);if(!isdigit(ch))break;res=(res<<3)+(res<<1)+(ch&15);++readPos;}if(negative)res=-res;return true;}
constexpr int kWriteBufferSize=1<<15;static int writePos=0;static char writeBuffer[kWriteBufferSize];
inline void writeChar(char x){if(writePos==kWriteBufferSize){fwrite(writeBuffer,1,kWriteBufferSize,stdout);writePos=0;}writeBuffer[writePos++]=x;}
struct Flusher{inline~Flusher(){if(writePos)fwrite(writeBuffer,1,writePos,stdout);writePos=0;}}flusher;
inline void writeInt(int x){static char s[32];if(x<0){writeChar('-');x=-x;}int n=0;for(;x||!n;x/=10)s[n++]='0'+x%10;for(;n>0;writeChar(s[--n])){}}
//clang-format on
const int PRIME_WHEEL[4]={2,3,5,7};
const int PRIME_LCM=2*3*5*7;
const int COPRIME_CNT=48;
const int COPRIMES[COPRIME_CNT]={
1,11,13,17,19,23,29,31,37,41,43,47,
53,59,61,67,71,73,79,83,89,97,101,103,
107,109,113,121,127,131,137,139,143,149,151,157,
163,167,169,173,179,181,187,191,193,197,199,209};
struct PrimeIterator{
inline PrimeIterator(int n=30){
precompute_();
init(n);
}
inline void init(int n){
int size=n/PRIME_LCM+1;
sieve_.assign(size,0);
sieve_[0]=1;
int bound=static_cast<int>(sqrt(n)+1);
memcpy(mul_,mulInit_,sizeof(mul_));
auto*sieve=sieve_.data();
const auto*sieveEnd=sieve+size;
for(int base=0;base<=bound;base+=PRIME_LCM,++sieve){
for(int i=0;i<COPRIME_CNT;++i){
if(!((*sieve>>i)&1)){
int v=base+COPRIMES[i],vv=v*v;
tag_(
coprimesInv_[vv%PRIME_LCM],
sieve_.data()+vv/PRIME_LCM,
sieveEnd,
mul_[i],
nextIdx_[i]);
}
for(int k=0;k<COPRIME_CNT;++k)mul_[i][k]+=mulStep_[i][k];
}
}
}
inline void iterate(int n,const std::function<void(int)>&processor){
for(int p:PRIME_WHEEL){
if(p<n){
processor(p);
}
}
int base=0;
for(const auto&sieve:sieve_){
for(int idx=0;idx<COPRIME_CNT;++idx){
if((sieve>>idx)&1)continue;
int v=base+COPRIMES[idx];
if(v>=n)break;
processor(v);
}
base+=PRIME_LCM;
if(base>=n)break;
}
}
inline void precompute_(){
memset(coprimesInv_,0xFF,sizeof(coprimesInv_));
for(int i=0;i<COPRIME_CNT;++i){
coprimesInv_[COPRIMES[i]]=i;
}
for(int i=0;i<COPRIME_CNT;++i){
for(int j=0;j<COPRIME_CNT;++j){
int sum=COPRIMES[i]+COPRIMES[j],step=1,delta=0;
if(sum>=PRIME_LCM){
sum-=PRIME_LCM;
++delta;
}
for(;coprimesInv_[sum]<0;++step){
sum+=COPRIMES[i];
if(sum>=PRIME_LCM){
sum-=PRIME_LCM;
++delta;
}
}
nextIdx_[i][j]=coprimesInv_[sum];
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
int mul_[COPRIME_CNT][COPRIME_CNT];
int coprimesInv_[PRIME_LCM];
int mulInit_[COPRIME_CNT][COPRIME_CNT];
int mulStep_[COPRIME_CNT][COPRIME_CNT];
int nextIdx_[COPRIME_CNT][COPRIME_CNT];
vector<long long>sieve_;
};
const int MAXQ=100000;
short answerX[MAXQ],answerY[MAXQ];
struct Query{
int n,idx;
inline Query(){}
inline void init(int idx_){
idx=idx_;
readInt(n);
if(n==2){
answerX[idx]=1;
answerY[idx]=1;
}else if(n==3){
answerX[idx]=2;
answerY[idx]=1;
}else if(n==5){
answerX[idx]=2;
answerY[idx]=2;
}else{
answerX[idx]=-1;
}
}
};
Query queries[MAXQ];
int main(){
int taskNumber;
readInt(taskNumber);
for(int taskIdx=0;taskIdx<taskNumber;++taskIdx){
queries[taskIdx].init(taskIdx);
}
sort(queries,queries+taskNumber,[](const auto&lhs,const auto&rhs){
return lhs.n<rhs.n;
});
PrimeIterator pi(queries[taskNumber-1].n+1);
short curX=0,curY=0;
Query*queryPnt=queries,*queryEnd=queries+taskNumber;
pi.iterate(
queries[taskNumber-1].n+1,
[&curX,&curY,&queryPnt,&queryEnd](int prime){
++curY;
if(curX<curY){
++curX;
curY=1;
}
for(;queryPnt<queryEnd&&queryPnt->n<=prime;++queryPnt){
if(queryPnt->n==prime){
answerX[queryPnt->idx]=curX;
answerY[queryPnt->idx]=curY;
}
}
});
for(int taskIdx=0;taskIdx<taskNumber;++taskIdx){
if(answerX[taskIdx]<0){
      writeChar('-');
      writeChar('1');
}else{
writeInt(answerX[taskIdx]);
      writeChar(' ');
writeInt(answerY[taskIdx]);
}
    writeChar('\n');
}
return 0;
}
