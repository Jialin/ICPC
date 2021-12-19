#pragma once

#ifdef LOCAL
using namespace std;

template<typename T>
inline string totype(const vector<T>& vs);

template<typename X, typename Y>
inline string totype(const pair<X, Y>& vs);

template<typename T>
inline string tostring(const vector<T>& vs);

template<typename X, typename Y>
inline string tostring(const pair<X, Y>& vs);

template<typename... VS>
inline string tostring1(VS const&... vs);

template<typename... VS>
inline string tostring2(VS const&... vs);
#endif
