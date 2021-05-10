#include <iostream>
#include "src/main.hxx"

using namespace std;




int main(int argc, char **argv) {
  DiGraph<> x;
  x.addEdge(1, 2);
  x.addEdge(2, 3);
  x.addEdge(2, 3);
  // x.removeVertex(2);
  cout << "order: " << x.order() << " size: " << x.size() << " {\n";
  for (int v : x.vertices()) {
    cout << "  " << v << " <-";
    for (int u : x.inEdges(v))
      cout << " " << u;
    cout << "\n";
  }
  cout << "}\n";
  return 0;
}
