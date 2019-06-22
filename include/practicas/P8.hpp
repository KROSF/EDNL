#ifndef PRACTICAS_P8_HPP
#define PRACTICAS_P8_HPP

#include <cmath>
#include "grafos/alg.hpp"

using grafos::matriz;
using grafos::Particion;
using grafos::ma::Grafo;
using grafos::pmc::Floyd;
using grafos::pmc::GrafoP;

struct CC {
  double x, y;
  double distanciaEuclidea(const CC& c) const {
    return std::sqrt(std::pow(c.x - x, 2) - std::pow(c.y - y, 2));
  }
};

std::tuple<vector<vector<double>>, matriz<double>> Tombuctu(
    const vector<CC>& ciudades, const Grafo& carreteras) {
  size_t n{ciudades.size()};
  Particion P{n};
  GrafoP<double> G(n);
  int repre_1{1}, repre_2{0};
  matriz<vertice<double>> FP;
  for (size_t v = 0; v < n; ++v) {
    repre_1 = P.encontrar[v];
    for (size_t w = 0; w < n; ++w) {
      if (carreteras[v][w]) {
        repre_2 = P.encontrar[w];
        P.unir(repre_1, repre_2);
        G[v][w] = G[w][v] = ciudades[v].distanciaEuclidea(ciudades[w]);
      }
    }
  }
  vector<vector<size_t>> islas;
  size_t n_islas{0};
  for (size_t v = 0; v < n; ++v) {
    repre_1 = P.encontrar(v);
    for (size_t w = v; v < n; ++w) {
      if (repre_1 == P.encontrar(w)) {
        islas[n_islas].push_back(w);
      }
    }
  }
  return {, Floyd(G, FP)};
}
#endif