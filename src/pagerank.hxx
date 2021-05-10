#pragma once
#include <vector>
#include <utility>

using std::vector;
using std::move;




template <class T>
struct PagerankOptions {
  T damping;
  T tolerance;
  int maxIterations;

  PagerankOptions(T damping=0.85, T tolerance=1e-6, int maxIterations=10000) :
  damping(damping), tolerance(tolerance), maxIterations(maxIterations) {}
};


template <class T>
struct PagerankResult {
  vector<T> ranks;
  float rounds;
  float time;

  PagerankResult(vector<T>& ranks, float rounds=0, float time=0) :
  ranks(move(ranks)), rounds(rounds), time(time) {}
};
