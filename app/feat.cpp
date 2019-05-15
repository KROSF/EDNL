#include <iostream>
#include "grafos/alg.hpp"
#include "grafos/io.hpp"
using namespace grafos::pmc;
using std::vector;
int main(void) {
  vector<alg::vertice<unsigned>> P;
  GrafoP<unsigned> G("files/grafos/dijkstrainv.txt");
  vector<unsigned> Dinv = alg::DijkstraInv(G, 0, P);
  for (size_t i = 0; i < G.numVert(); ++i)
    std::cout << i << " Coste(" << Dinv[i]
              << "): " << alg::camino<unsigned>(i, 0, P, true) << std::endl;
}