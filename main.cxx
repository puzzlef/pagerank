#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, int repeat) {
  using T = float;
  enum NormFunction { L0=0, L1=1, L2=2, Li=3 };
  vector<T> *init = nullptr;
  float damping = 0.85;

  // Use L1-norm for convergence check.
  for (float tolerance=1e-1; tolerance>=1e-15; tolerance/=10) {
    // Find unordered pagerank using a single thread.
    auto a0 = pagerankMonolithicSeq<false>(x, xt, init, {repeat, L1, damping, tolerance});
    auto e0 = l1Norm(a0.ranks, a0.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeqUnordered {tol_norm: L1, tolerance: %.0e}\n", a0.time, a0.iterations, e0, tolerance);
    // Find ordered pagerank using a single thread.
    auto a1 = pagerankMonolithicSeq<true>(x, xt, init, {repeat, L1, damping, tolerance});
    auto e1 = l1Norm(a1.ranks, a0.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeqOrdered   {tol_norm: L1, tolerance: %.0e}\n", a1.time, a1.iterations, e1, tolerance);
  }

  // Use L2-norm for convergence check.
  for (float tolerance=1e-1; tolerance>=1e-15; tolerance/=10) {
    // Find unordered pagerank using a single thread.
    auto a0 = pagerankMonolithicSeq<false>(x, xt, init, {repeat, L2, damping, tolerance});
    auto e0 = l1Norm(a0.ranks, a0.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeqUnordered {tol_norm: L2, tolerance: %.0e}\n", a0.time, a0.iterations, e0, tolerance);
    // Find ordered pagerank using a single thread.
    auto a1 = pagerankMonolithicSeq<true>(x, xt, init, {repeat, L2, damping, tolerance});
    auto e1 = l1Norm(a1.ranks, a0.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeqOrdered   {tol_norm: L2, tolerance: %.0e}\n", a1.time, a1.iterations, e1, tolerance);
  }

  // Use Li-norm for convergence check.
  for (float tolerance=1e-1; tolerance>=1e-15; tolerance/=10) {
    // Find unordered pagerank using a single thread.
    auto a0 = pagerankMonolithicSeq<false>(x, xt, init, {repeat, Li, damping, tolerance});
    auto e0 = l1Norm(a0.ranks, a0.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeqUnordered {tol_norm: Li, tolerance: %.0e}\n", a0.time, a0.iterations, e0, tolerance);
    // Find ordered pagerank using a single thread.
    auto a1 = pagerankMonolithicSeq<true>(x, xt, init, {repeat, Li, damping, tolerance});
    auto e1 = l1Norm(a1.ranks, a0.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeqOrdered   {tol_norm: Li, tolerance: %.0e}\n", a1.time, a1.iterations, e1, tolerance);
  }
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int repeat = argc>2? stoi(argv[2]) : 5;
  printf("Loading graph %s ...\n", file);
  auto x  = readMtxOutDiGraph(file);  println(x);
  // auto fl = [](auto u) { return true; };
  // selfLoopU(x, None(), fl); print(x); printf(" (selfLoopAllVertices)\n");
  auto xt = transposeWithDegree(x);   print(xt); printf(" (transposeWithDegree)\n");
  runPagerank(x, xt, repeat);
  printf("\n");
  return 0;
}
