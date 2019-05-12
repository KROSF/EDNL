#include <iostream>
#include <string>
#include <vector>
#include "grafos/alg.hpp"
#include "grafos/io.hpp"

using namespace grafos;
using namespace pmc;
using std::cout;
using std::endl;
using std::vector;

int main(void) {
  std::string path("files/grafopmc.txt");
  GrafoP<int> G(path);
  cout << GrafoP<int>::INFINITO << endl;
  vector<GrafoP<int>::vertice> vertices(G.numVert());
  // cout << alg::Dijkstra(G, 2, vertices) << endl;
  cout << G << endl;
}