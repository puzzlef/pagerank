#include <cmath>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, bool show) {
  int repeat = 5; float damping = 0.85f;
  vector<float> *init = nullptr;

  // Find pagerank using default tolerance 10^-6.
  auto a1 = pagerankMonolithic(xt, init, {repeat, damping});
  auto e1 = l1Norm(a1.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerank\n", a1.time, a1.iterations, e1);
  if (show) println(a1.ranks);

  // Find pagerank using custom tolerance.
  for (int i=0; i<=20; i++) {
    float tolerance = pow(10.0f, -i/2) / (i&1? 2:1);
    auto a2 = pagerankMonolithic(xt, init, {repeat, damping, tolerance});
    auto e2 = l1Norm(a2.ranks, a1.ranks);
    printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerank [tolerance=%.0e]\n", a2.time, a2.iterations, e2, tolerance);
  }
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
