#include <iostream>
#include "grafos/alg.hpp"
#include "grafos/io.hpp"

using namespace grafos;
using namespace pmc;
using namespace alg;

template <typename C>
double CementosZuelandia(const GrafoP<C>& G, vertice<C> capital,
                         const vector<C>& diario) {
  vector<vertice<C>> P;
  vector<C> D{Dijkstra(G, capital, P)};
  std::cout << D << std::endl;
  vector<C> Dinv{DijkstraInv(G, capital, P)};
  std::cout << Dinv << std::endl << "   ";
  double km{0};
  D[capital] = Dinv[capital] = 0;
  for (vertice<C> v = 0; v < D.size(); ++v) {
    km += ((Dinv[v] + D[v]) * diario[v]);
    std::cout << km << " ";
  }
  return km;
}

int main(void) {
  GrafoP<short> G("files/grafos/zuelandia.txt");
  vector<short> diario{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  std::cout << CementosZuelandia(G, 0, diario) << std::endl;
}