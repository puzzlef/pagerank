#pragma once
#include <algorithm>
#include "_main.hxx"
#include "vertices.hxx"
#include "edges.hxx"
#include "pagerank.hxx"

using std::swap;




template <class T>
void pagerankPushOnce(vector<T>& a, const vector<T>& r, const vector<int>& vto, const vector<int>& eto, int N, T p) {
  fill(a, (1-p)/N);
  for (int u=0; u<N; u++) {
    int d = vto[u+1] - vto[u];
    if (d > 0) addValueAt(a, p*r[u]/d, slice(eto, vto[u], vto[u+1]));
    else addValue(a, p*r[u]/N);
  }
}

template <class T>
int pagerankPushLoop(vector<T>& a, vector<T>& r, const vector<int>& vto, const vector<int>& eto, int N, T p, T E, int L) {
  int l = 0;
  T e0 = T();
  for (; l<L; l++) {
    pagerankPushOnce(a, r, vto, eto, N, p);
    T e1 = absError(a, r);
    if (e1<E || e1==e0) break;
    swap(a, r);
    e0 = e1;
  }
  return l;
}

template <class T>
int pagerankPushCore(vector<T>& a, vector<T>& r, const vector<int>& vto, const vector<int>& eto, int N, const vector<T> *q, T p, T E, int L) {
  if (q) copy(r, *q);
  else fill(r, T(1)/N);
  return pagerankPushLoop(a, r, vto, eto, N, p, E, L);
}


// Find pagerank by pushing contribution to out-vertices.
// @param x original graph
// @param q initial ranks (optional)
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G, class T=float>
PagerankResult<T> pagerankPush(const G& x, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  T    p = o.damping;
  T    E = o.tolerance;
  int  L = o.maxIterations, l;
  auto vto = sourceOffsets(x);
  auto eto = destinationIndices(x);
  int  N   = x.order();
  vector<T> a(N), r(N);
  float t = measureDuration([&]() { l = pagerankPushCore(a, r, vto, eto, N, q, p, E, L); }, o.repeat);
  return {vertexContainer(x, a), l, t};
}
