namespace ss { namespace utils {

inline string toString(const vector<int>& vs) {
  ostringstream ss;
  ss << '[';
  bool first = true;
  for (auto v : vs) {
    if (first) {
      first = false;
    } else {
      ss << ' ';
    }
    ss << v;
  }
  ss << ']';
  return ss.str();
}

}} // namespace ss::utils
