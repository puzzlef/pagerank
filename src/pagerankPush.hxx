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
  T e0 = T();
  int l = 0;
  for (; l<L; l++) {
    pagerankPushOnce(a, r, x, p);
    T e1 = absError(a, r);
    if (e1<E || e1==e0) break;
    swap(a, r);
    e0 = e1;
  }
  return l;
}


template <class G, class T=float>
PagerankResult<T> pageRankPush(G& x, vector<T> *init=nullptr, PagerankOptions<T> o={}) {
  int N = x.order(), l;
  auto a = x.vertexContainer(T());
  auto r = x.vertexContainer(T());
  if (init) r = *init;
  else fill(r, T(1)/N);
  float t = measureDuration([&]() { l = pagerankPushLoop(a, r, x, o.damping, o.tolerance, o.maxIterations); });
  fillAt(a, T(), x.nonVertices());
  return {a, l, t};
}
