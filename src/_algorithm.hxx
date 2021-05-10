#pragma once
#include <vector>
#include <algorithm>

using std::vector;
using std::find;
using std::count;
using std::count_if;




// FIND
// ----

template <class J, class T>
auto find(const J& x, const T& v) {
  return find(x.begin(), x.end(), v);
}

template <class J, class T>
int findIndex(const J& x, const T& v) {
  auto i = find(x.begin(), x.end(), v);
  return i==x.end()? -1 : i-x.begin();
}




// COUNT-*
// -------

template <class J, class T>
int count(const J& x, const T& v) {
  return count(x.begin(), x.end(), v);
}


template <class I, class F>
int countIf(I ib, I ie, F fn) {
  return count_if(ib, ie, fn);
}

template <class J, class F>
int countIf(const J& x, F fn) {
  return count_if(x.begin(), x.end(), fn);
}




// ERASE
// -----

template <class T>
void eraseIndex(vector<T>& x, int i) {
  x.erase(x.begin()+i);
}

template <class T>
void eraseIndex(vector<T>& x, int i, int I) {
  x.erase(x.begin()+i, x.begin()+I);
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




// FILL-AT
// -------

template <class T, class I>
void fillAt(T *a, T v, I&& is) {
  for (int i : is)
    a[i] = v;
}

template <class T, class I>
void fillAt(vector<T>& a, T v, I&& is) {
  fillAt(a.data(), v, is);
}




// ADD-VALUE
// ---------

template <class T>
void addValue(T *a, int N, T v) {
  for (int i=0; i<N; i++)
    a[i] += v;
}

template <class T>
void addValue(vector<T>& a, T v) {
  addValue(a.data(), a.size(), v);
}




// ADD-VALUE-AT
// ------------

template <class T, class I>
void addValueAt(T *a, T v, I&& is) {
  for (int i : is)
    a[i] += v;
}

template <class T, class I>
void addValueAt(vector<T>& a, T v, I&& is) {
  addValueAt(a.data(), v, is);
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
