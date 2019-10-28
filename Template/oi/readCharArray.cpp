namespace oi {

void readCharArray(char res[]) {
  int ch;
  while ((ch = getchar()) != EOF && isspace(ch)) {
  }
  int idx = 0;
  res[idx++] = CAST<char>(ch);
  while ((ch = getchar()) != EOF && !isspace(ch)) {
    res[idx++] = CAST<char>(ch);
  }
  res[idx] = '\0';
}

} // namespace oi
