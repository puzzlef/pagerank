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

  // Find unordered pagerank using a single thread.
  auto a0 = pagerankMonolithicSeq<false>(x, xt, init, {repeat});
  auto e0 = l1Norm(a0.ranks, a0.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeqUnordered\n", a0.time, a0.iterations, e0);
  // Find ordered pagerank using a single thread.
  auto a1 = pagerankMonolithicSeq<true>(x, xt, init, {repeat});
  auto e1 = l1Norm(a1.ranks, a0.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankSeqOrdered\n", a1.time, a1.iterations, e1);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int repeat = argc>2? stoi(argv[2]) : 5;
  printf("Loading graph %s ...\n", file);
  auto x  = readMtxOutDiGraph(file);  println(x);
  auto fl = [](auto u) { return true; };
  selfLoopU(x, None(), fl); print(x); printf(" (selfLoopAllVertices)\n");
  auto xt = transposeWithDegree(x);   print(xt); printf(" (transposeWithDegree)\n");
  runPagerank(x, xt, repeat);
  printf("\n");
  return 0;
}
