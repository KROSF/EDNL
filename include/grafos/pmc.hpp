#ifndef GRAFO_PMC_HPP
#define GRAFO_PMC_HPP
#include <fstream>
#include <iomanip>
#include <limits>
#include <ostream>
#include <string>
#include <vector>
#include "grafos/lista.hpp"
#include "grafos/ma.hpp"

using std::vector;

namespace grafos {
namespace pmc {
template <typename T>
class GrafoP {
 public:
  using tCoste = T;
  using vertice = std::size_t;
  using tCamino = Lista<vertice>;
  inline static const tCoste INFINITO = std::numeric_limits<T>::max();
  struct arista {
    explicit arista(vertice v = vertice(), vertice w = vertice(),
                    tCoste c = tCoste())
        : orig{v}, dest{w}, coste{c} {}
    vertice orig, dest;
    tCoste coste;
  };
  explicit GrafoP(std::size_t n) : costes(n, vector<tCoste>(n, INFINITO)) {}
  explicit GrafoP(const std::string& path);
  GrafoP(const ma::Grafo& g);
  std::size_t numVert() const { return costes.size(); }
  const vector<tCoste>& operator[](vertice v) const { return costes[v]; }
  vector<tCoste>& operator[](vertice v) { return costes[v]; }
  bool esDirigido() const;

 private:
  vector<vector<tCoste>> costes;
};

template <typename T>
GrafoP<T>::GrafoP(const std::string& path) {
  std::ifstream file(path);
  unsigned n;
  file >> n;
  costes = vector<vector<T>>(n, vector<T>(n));
  for (vertice i = 0; i < n; ++i) {
    for (vertice j = 0; j < n; ++j) {
      file >> costes[i][j];
    }
  }
  file.close();
}

template <typename T>
GrafoP<T>::GrafoP(const ma::Grafo& g)
    : costes(g.numVert(), vector<T>(g.numVert())) {
  const size_t n = g.numVert();
  for (vertice i = 0; i < n; i++) {
    for (vertice j = 0; j < n; j++) {
      costes[i][j] = g[i][j] ? 1 : GrafoP<T>::INFINITO;
    }
  }
}

template <typename T>
bool GrafoP<T>::esDirigido() const {
  bool s = true;
  const std::size_t n = numVert();
  vertice i = 0;
  while (s && i < n) {
    vertice j = i + 1;
    while (s && j < n) {
      s = (costes[i][j] == costes[j][i]);
      ++j;
    }
    ++i;
  }
  return !s;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const GrafoP<T>& g) {
  using vertice = typename GrafoP<T>::vertice;
  const size_t n = g.numVert();
  os << n << " vertices" << std::endl;
  os << "    ";
  for (vertice j = 0; j < n; j++) os << std::setw(4) << j;
  os << std::endl;
  for (vertice i = 0; i < n; i++) {
    os << std::setw(4) << i;
    for (vertice j = 0; j < n; j++) {
      os << std::setw(4);
      if (g[i][j] == GrafoP<T>::INFINITO) {
        os << "-";
      } else {
        os << g[i][j];
      }
    }
    os << std::endl;
  }
  return os;
}

}  // namespace pmc
}  // namespace grafos
#endif