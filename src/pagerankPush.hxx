#pragma once
#include <algorithm>
#include "_main.hxx"
#include "pagerank.hxx"

using std::swap;




template <class C, class G, class T>
void pagerankPushOnce(C& a, C& r, G& x, T p) {
  int N = x.order();
  fill(a, (1-p)/N);
  for (int u : x.vertices()) {
    int d = x.degree(u);
    if (d > 0) addValueAt(a, p*r[u]/d, x.edges(u));
    else addValue(a, p*r[u]/N);
  }
}

template <class C, class G, class T>
int pagerankPushLoop(C& a, C& r, G& x, T p, T E, int L) {
  int l = 0;
  T e0 = T();
  for (; l<L; l++) {
    pagerankPushOnce(a, r, x, p);
    T e1 = absError(a, r);
    if (e1<E || e1==e0) break;
    swap(a, r);
    e0 = e1;
  }
  return l;
}


// Find pagerank by pushing contribution to out-vertices.
// @param x original graph
// @param init initial ranks
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, rounds, time}
template <class G, class T=float>
PagerankResult<T> pageRankPush(G& x, vector<T> *init=nullptr, PagerankOptions<T> o={}) {
  T    p = o.damping;
  T    E = o.tolerance;
  int  L = o.maxIterations;
  int  N = x.order(), l;
  auto a = x.vertexContainer(T());
  auto r = x.vertexContainer(T());
  if (init) r = *init;
  else fill(r, T(1)/N);
  float t = measureDuration([&]() { l = pagerankPushLoop(a, r, x, p, E, L); });
  fillAt(a, T(), x.nonVertices());
  return {a, l, t};
}
