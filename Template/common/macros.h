#define ALL(vs) vs.begin(), vs.end()
#define CAST static_cast
#define FILL(vs, v) fill(ALL(vs), v)

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORR(i, a, b) for (int i = (a); i >= (b); --i)
#define FORIF(i, a, b, condition)                                                                  \
  for (int i = (a); i < (b); ++i)                                                                  \
    if (condition)
#define FORRIF(i, a, b, condition)                                                                 \
  for (int i = (a); i >= (b); --i)                                                                 \
    if (condition)

#define FOREDGE(i, vs, j) for (int i = (vs).lastOut[j]; i >= 0; i = (vs).nxtOut[i])
#define SIZE(vs) static_cast<int>((vs).size())
#define FORSIZE(i, vs) for (int i = 0; i < SIZE(vs); ++i)
#define SORT(vs) sort(ALL(vs))
#define UNIQUE(vs) vs.erase(unique(ALL(vs)), vs.end())
#define SORTUNIQUE(vs)                                                                             \
  SORT(vs);                                                                                        \
  UNIQUE(vs)
#define INDEX(vs, v) CAST<int>(lower_bound(ALL(vs), v) - vs.begin())
#define MMIN(a, b) a = min(a, b)
#define MMAX(a, b) a = max(a, b)
