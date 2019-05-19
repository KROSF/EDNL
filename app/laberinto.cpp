#include <iostream>
#include <tuple>
#include "grafos/alg.hpp"
#include "grafos/io.hpp"

using namespace grafos;
using namespace pmc;
using namespace alg;

template <typename tCoste>
std::tuple<tCoste, tCamino<tCoste>> Laberinto(
    size_t dim, const Lista<arista<tCoste>>& paredes, vertice<tCoste> inicio,
    vertice<tCoste> fin) {
  GrafoP<tCoste> L(dim * dim);
  for (vertice<tCoste> v = 0; v < dim * dim; ++v) {
    if (v < dim * (dim - 1)) {
      L[v][v + dim] = L[v + dim][v] = 1;
    }
    if (v % dim != dim - 1) {
      L[v][v + 1] = L[v + 1][v] = 1;
    }
  }
  // std::cout << L << std::endl;
  for (auto it = paredes.primera(); it != paredes.fin();
       it = paredes.siguiente(it)) {
    const arista<tCoste>& p = paredes.elemento(it);
    L[p.orig][p.dest] = L[p.dest][p.orig] = GrafoP<tCoste>::INFINITO;
  }
  // std::cout << L << std::endl;
  vector<vertice<tCoste>> P;
  vector<tCoste> D{Dijkstra(L, inicio, P)};
  // std::cout << D << std::endl;
  return {D[fin], camino<tCoste>(inicio, fin, P)};
}

std::ostream& operator<<(std::ostream& os, const arista<int>& a) {
  return os << "(" << a.orig << ", " << a.dest << ") = " << a.coste;
}

int main(void) {
  std::vector<arista<int>> muros{
      arista<int>(0, 1),   arista<int>(2, 3),   arista<int>(6, 7),
      arista<int>(8, 9),   arista<int>(7, 12),  arista<int>(8, 13),
      arista<int>(10, 11), arista<int>(13, 14), arista<int>(11, 16),
      arista<int>(12, 17), arista<int>(18, 19), arista<int>(15, 16),
      arista<int>(20, 21), arista<int>(17, 22), arista<int>(18, 23),
      arista<int>(22, 23)};
  Lista<arista<int>> m;

  for (auto e : muros) {
    m.insertar(e, m.fin());
  }
  for (auto it = m.primera(); it != m.fin(); it = m.siguiente(it)) {
    std::cout << m.elemento(it) << std::endl;
  }
  auto [coste, path] = Laberinto<int>(5, m, 2, 22);
  std::cout << coste << std::endl;
  for (auto it = path.primera(); it != path.fin(); it = path.siguiente(it)) {
    std::cout << path.elemento(it) << " ";
  }
}