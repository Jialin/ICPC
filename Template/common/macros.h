#define ALL(vs) vs.begin(), vs.end()
#define CAST static_cast
#define FILL(vs, v) fill(ALL(vs), v)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FOREDGE(i, j, vs) for (int i = vs.lastOut[j]; i >= 0; i = vs.nxtOut[i])
#define FORIF(i, a, b, condition)                                                                  \
  for (int i = (a); i < (b); ++i)                                                                  \
    if (condition)
#define FORSIZE(i, vs) for (int i = 0; i < static_cast<int>(vs.size()); ++i)
#define SIZE(vs) static_cast<int>(vs.size())
#define SORT(vs) sort(ALL(vs))
#define UNIQUE(vs) vs.erase(unique(ALL(vs)), vs.end())
#define SORTUNIQUE(vs)                                                                             \
  SORT(vs);                                                                                        \
  UNIQUE(vs)
#define INDEX(vs, v) lower_bound(ALL(vs), v) - vs.begin()
