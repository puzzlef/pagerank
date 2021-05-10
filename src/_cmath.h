#pragma once
#include <cmath>
#include <vector>

using std::vector;
using std::ceil;




// CEIL-DIV
// --------

template <class T>
T ceilDiv(T x, T y) {
  if (is_floating_point<T>()) return ceil(x/y);
  else return (x + y-1) / y;
}




// FILL
// ----

template <class T>
void fill(T *a, int N, T v) {
  for (int i=0; i<N; i++)
    a[i] = v;
}

template <class T>
void fill(vector<T>& a, T v) {
  fill(a.begin(), a.end(), v);
}




// ABS-ERROR
// ---------

template <class T>
auto absError(T *x, T *y, int N) {
  T a = T();
  for (int i=0; i<N; i++)
    a += abs(x[i] - y[i]);
  return a;
}

template <class T>
auto absError(vector<T>& x, vector<T>& y) {
  return absError(x.data(), y.data(), x.size());
}
