#ifndef GRAFO_PMC_HPP
#define GRAFO_PMC_HPP
#include <fstream>
#include <iomanip>
#include <limits>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>
#include "grafos/lista.hpp"
#include "grafos/ma.hpp"

using std::vector;

namespace grafos::pmc {
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
    bool operator==(const arista& a) const {
      return orig == a.orig && dest == a.dest && coste == a.coste;
    }
  };
  explicit GrafoP(std::size_t n) : costes(n, vector<tCoste>(n, INFINITO)) {}
  explicit GrafoP(std::string_view path);
  explicit GrafoP(const ma::Grafo& g);
  std::size_t numVert() const { return costes.size(); }
  const vector<tCoste>& operator[](vertice v) const { return costes[v]; }
  vector<tCoste>& operator[](vertice v) { return costes[v]; }
  bool esDirigido() const;

 private:
  vector<vector<tCoste>> costes;
};

template <typename T>
GrafoP<T>::GrafoP(std::string_view path) {
  std::ifstream file(path.data());
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
  for (vertice i = 0; i < n; ++i) {
    for (vertice j = 0; j < n; ++j) {
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
  const std::size_t n = g.numVert();
  std::size_t digits{0};
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = 0; j < n; ++j) {
      if (g[i][j] != GrafoP<T>::INFINITO &&
          static_cast<std::size_t>(g[i][j]) > digits) {
        digits = g[i][j];
      }
    }
  }
  digits = std::to_string(digits).size() + 1;
  os << "\033[1m\033[31m" << n << " vertices\n\033[32m"
     << std::string(digits, ' ');
  for (vertice j = 0; j < n; ++j) {
    os << std::setw(digits) << j;
  }
  os << "\033[00m\n";
  for (vertice i = 0; i < n; ++i) {
    os << "\033[1m\033[32m" << std::setw(digits) << i << "\033[00m"
       << std::setw(digits);
    for (vertice j = 0; j < n; ++j) {
      if (g[i][j] == GrafoP<T>::INFINITO) {
        os << std::setw(digits + 16) << "\033[1m\033[34m\u221E\033[00m";
      } else {
        os << std::setw(digits) << g[i][j];
      }
    }
    os << std::endl;
  }
  return os;
}

}  // namespace grafos::pmc
#endif