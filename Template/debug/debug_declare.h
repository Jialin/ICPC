#pragma once

#ifdef LOCAL
template<typename T>
inline string tostring(const vector<T>& vs);

template<typename X, typename Y>
inline string tostring(const pair<X, Y>& vs);
#endif
