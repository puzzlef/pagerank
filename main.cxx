#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(G& x, H& xt, bool show) {
  int repeat = 5;
  vector<float> *init = nullptr;

  // Find pagerank by pushing contribution to out-vertices.
  auto a1 = pagerankPush(x, init, {repeat});
  auto e1 = absError(a1.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankPush\n", a1.time, a1.iterations, e1);
  if (show) println(a1.ranks);

  // Find pagerank by pulling contribution from in-vertices.
  auto a2 = pagerankPull(xt, init, {repeat});
  auto e2 = absError(a2.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankPull\n", a2.time, a2.iterations, e2);
  if (show) println(a2.ranks);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  bool  show = argc > 2;
  printf("Loading graph %s ...\n", file);
  auto x  = readMtx(file); println(x);
  auto xt = transposeWithDegree(x); print(xt); printf(" (transposeWithDegree)\n");
  runPagerank(x, xt, show);
  printf("\n");
  return 0;
}
