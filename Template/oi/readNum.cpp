namespace oi {

template <typename T> void readNum(T &res) {
  int ch;
  while ((ch = getchar()) != EOF && !isdigit(ch) && ch != '+' && ch != '-') {
  }
  bool negative = ch == '-';
  res = isdigit(ch) ? ch - '0' : 0;
  while ((ch = getchar()) != EOF && isdigit(ch)) {
    res = (res << 3) + (res << 1) + (ch ^ 48);
  }
  if (negative) {
    res = -res;
  }
}

} // namespace oi
