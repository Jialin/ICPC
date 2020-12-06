#pragma once

using namespace std;

void debugv(int64_t v, const string& name) {
  fprintf(stderr, "int64_t`%s`= %lld", name.c_str(), v);
}

void debugv(int v, const string& name) {
  fprintf(stderr, "int`%s`= %d", name.c_str(), v);
}

void debugv(const char* v, const string& name) {
  fprintf(stderr, "char*`%s`= %s", name.c_str(), v);
}

void debugv(const string& v, const string& name) {
  fprintf(stderr, "string`%s`= %s", name.c_str(), v.c_str());
}

void debugv(const vector<int>& vs, const string& name) {
  fprintf(stderr, "vector<int>`%s`(size:%lu)= [", name.c_str(), vs.size());
  if (!vs.empty()) {
    fprintf(stderr, "%d", vs.front());
    for (int i = 1; i < (int)vs.size(); ++i) {
      fprintf(stderr, ",%d", vs[i]);
    }
  }
  fprintf(stderr, "]");
}

template<typename V>
void debugBit(V v, const string& name) {
  fprintf(stderr, "bit`%s`= ", name.c_str());
  if (v == 0) {
    fprintf(stderr, "0");
    return;
  }
  if (v < 0) {
    fprintf(stderr, "-");
    v = -v;
  }
  vector<int> bits;
  for (int cnt = 0; v > 0 && cnt < 256; ++cnt, v >>= 1) {
    bits.emplace_back(v & 1);
  }
  reverse(bits.begin(), bits.end());
  for (int bit : bits) {
    fprintf(stderr, "%d", bit);
  }
}