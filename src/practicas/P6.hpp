#include <algorithm>
#include <tuple>
#include "practicas/P6.hpp"
using namespace grafos::pmc;
using alg::Floyd;
using alg::vertice;
using grafos::matriz;

template <typename tCoste>
static std::tuple<std::size_t, std::size_t> diametro(const GrafoP<tCoste>& G) {
  matriz<vertice<tCoste>> P;
  matriz<tCoste> F{Floyd(G, P)};
  std::size_t n{F.dimension()};
  vector<std::size_t> diametro(n, 0);
  for (int i = 0, max = 0, max2 = 0; i < n; ++i, max = max2 = 0) {
    for (int j = 0; i < n; ++j) {
      if (F[i][j] > max && max <= max2) {
        max = F[i][j];
      } else if (F[i][j] > max2) {
        max2 = F[i][j];
      }
    }
    diametro.push_back(max + max2);
  }
  auto v = std::min_element(diametro.begin(), diametro.end());
  return { std::distance(diametro.begin(), v), *v }
}

template <typename T>
std::size_t Diametro(const GrafoP<T>& G) {
  auto [_, diam] = diametro(G);
  return diam;
}

template <typename T>
std::size_t PseudoCentro(const GrafoP<T>& G) {
  auto [nodo, _] = diametro(G);
  return nodo;
}