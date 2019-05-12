#include <iostream>
#include "grafos/alg.hpp"
#include "grafos/io.hpp"
using namespace grafos;
using namespace pmc;
using std::cout;
using std::endl;
using std::vector;
int main(int argc, char **argv) {
  if (argc > 1) {
    GrafoP<int> G(argv[1]);
    vector<alg::vertice<int>> P;
    auto D = alg::Dijkstra(G, 0, P);
    cout << D << endl;
    cout << P << endl;
    cout << G << endl;
  } else {
    cout << "Number of arguments incomplete" << endl;
  }
}