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
  for (vertice<C> v = 0; v < D.size(); ++v) {
    km += ((Dinv[v] + D[v]) * diario[v]);
    std::cout << km << " ";
  }
  return km;
}

template <typename T>
GrafoP<T> BigGrafo2(const vector<GrafoP<T>>& graphs,
                    const vector<vector<T>>& costes) {
  const size_t m{graphs.size()}, n{graphs[0].numVert()};
  GrafoP<T> BG(m * n);
  for (size_t i = 0, g = 0, d = 0; i < m; ++i, g += (m - i), d = 0) {
    for (vertice<T> v = 0; v < n; ++v) {
      for (vertice<T> w = 0; w < n; ++w) {
        BG[v + (n * i)][w + (n * i)] = graphs[i][v][w];
        if (v == w && i < m - 1) {
          for (size_t j = (n * i) + n, k = g; j < m * n; j += n, ++k) {
            BG[v + (n * i)][j + w] = BG[j + w][v + (n * i)] = costes[k][d];
          }
          ++d;
        }
      }
    }
    std::cout << d << "\n";
  }
  return BG;
}

int main(void) {
  GrafoP<int> B("files/grafos/bus.txt");
  GrafoP<int> T("files/grafos/tren.txt");
  GrafoP<int> got = BigGrafo<int>({B, T, B, T}, {{1, 2, 3, 4, 5, 6, 7, 8},
                                                 {9, 8, 7, 6, 5, 4, 3, 2},
                                                 {1, 2, 3, 2, 2, 2, 4, 1},
                                                 {1, 2, 3, 1, 2, 3, 1, 2},
                                                 {9, 8, 7, 6, 5, 4, 3, 2},
                                                 {1, 2, 3, 2, 2, 2, 4, 1}});
  std::cout << got << std::endl;
}