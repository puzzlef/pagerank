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
