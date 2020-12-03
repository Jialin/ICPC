#pragma once

using namespace std;

#define DEBUG_BEGIN(function, line)                                            \
  fprintf(stderr, "\033[94m==[%s][L%d]==\n", prettyFunction.c_str(), line)
#define DEBUG_END fprintf(stderr, "\n\033[0m")

void debugv(
    int64_t v, const string& name, const string& prettyFunction, int line) {
  DEBUG_BEGIN(prettyFunction, line);
  fprintf(stderr, "int64_t`%s`= %lld", name.c_str(), v);
  DEBUG_END;
}

void debugv(int v, const string& name, const string& prettyFunction, int line) {
  DEBUG_BEGIN(prettyFunction, line);
  fprintf(stderr, "int`%s`= %d", name.c_str(), v);
  DEBUG_END;
}

void debugv(
    const char* v, const string& name, const string& prettyFunction, int line) {
  DEBUG_BEGIN(prettyFunction, line);
  fprintf(stderr, "char*`%s`= %s", name.c_str(), v);
  DEBUG_END;
}

void debugv(
    const string& v,
    const string& name,
    const string& prettyFunction,
    int line) {
  debugv(v.c_str(), name, prettyFunction, line);
  DEBUG_BEGIN(prettyFunction, line);
  fprintf(stderr, "string`%s`= %s", name.c_str(), v.c_str());
  DEBUG_END;
}

void debugv(
    const vector<int>& vs,
    const string& name,
    const string& prettyFunction,
    int line) {
  DEBUG_BEGIN(prettyFunction, line);
  fprintf(stderr, "vector<int>`%s`(size:%lu)= [", name.c_str(), vs.size());
  if (!vs.empty()) {
    fprintf(stderr, "%d", vs.front());
    for (int i = 1; i < (int)vs.size(); ++i) {
      fprintf(stderr, ",%d", vs[i]);
    }
  }
  fprintf(stderr, "]");
  DEBUG_END;
}
