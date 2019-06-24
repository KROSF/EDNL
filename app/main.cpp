#include <iostream>
#include "grafos/alg.hpp"
#include "grafos/io.hpp"

using namespace grafos;
using namespace pmc;
using alg::Dijkstra;
using alg::DijkstraInv;
using alg::vertice;
using std::cout;
using std::endl;
using std::vector;

template <typename C>
C UnSoloTransbordo(const GrafoP<C>& tren, const GrafoP<C>& bus,
                   vertice<C> origen, vertice<C> destino) {
  vector<vertice<C>> P;
  vector<C> DTren{Dijkstra(tren, origen, P)};
  vector<C> DInvTren{DijkstraInv(tren, destino, P)};
  vector<C> DBus{Dijkstra(bus, origen, P)};
  vector<C> DInvBus{DijkstraInv(bus, destino, P)};
  const size_t n = tren.numVert();
  vector<C> min_elem(2 * n);
  for (size_t i = 0; i < n; ++i) {
    min_elem[i] = DTren[i] + DInvBus[i];
    min_elem[n + i] = DBus[i] + DInvTren[i];
  }
  cout << DTren << endl
       << DInvTren << endl
       << DBus << endl
       << DInvBus << endl
       << min_elem << endl;
  return *std::min_element(min_elem.begin(), min_elem.end());
}

int main(void) {
  GrafoP<int> B("files/grafos/bus.txt");
  GrafoP<int> T("files/grafos/tren.txt");
  cout << UnSoloTransbordo(T, B, 0, 7);
}