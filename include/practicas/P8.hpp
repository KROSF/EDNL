#ifndef PRACTICAS_P8_HPP
#define PRACTICAS_P8_HPP

#include <cmath>
#include <numeric>
#include "grafos/alg.hpp"

using grafos::matriz;
using grafos::Particion;
using grafos::ma::Grafo;
using grafos::pmc::GrafoP;
using grafos::pmc::alg::Floyd;
using grafos::pmc::alg::vertice;

template <typename T>
struct SumNotInf {
  T operator()(T a, T b) const {
    return ((b != GrafoP<T>::INFINITO) ? a + b : a);
  }
};

struct Ciudad {
  double x, y;
  double distancia(const Ciudad& c) const {
    return std::sqrt(std::pow(c.x - x, 2) + std::pow(c.y - y, 2));
  }
};

std::tuple<vector<vector<size_t>>, matriz<double>> Tombuctu(
    const vector<Ciudad>& ciudades, const Grafo& carreteras) {
  size_t n{ciudades.size()};
  Particion P{static_cast<int>(n)};
  GrafoP<double> G(n);
  int repre_1{1}, repre_2{0};
  matriz<vertice<double>> FP;
  for (size_t v = 0; v < n; ++v) {
    repre_1 = P.encontrar(v);
    for (size_t w = v; w < n; ++w) {
      if (carreteras[v][w]) {
        repre_2 = P.encontrar(w);
        P.unir(repre_1, repre_2);
        G[v][w] = G[w][v] = ciudades[v].distancia(ciudades[w]);
      }
    }
  }
  repre_1 = P.encontrar(0);
  vector<vector<size_t>> islas(1, vector<size_t>(1, 0));
  size_t n_islas{0};
  for (size_t v = 1; v < n; ++v) {
    if (repre_1 == P.encontrar(v)) {
      islas[n_islas].push_back(v);
    } else {
      ++n_islas;
      repre_1 = P.encontrar(v);
      islas.push_back(vector<size_t>(1, v));
    }
  }
  return {islas, Floyd(G, FP)};
}

vector<vertice<double>> Tombuctu2(const vector<Ciudad>& ciudades,
                                  const Grafo& carreteras) {
  auto [islas, floyd] = Tombuctu(ciudades, carreteras);

  size_t i_isla, f_isla, n_isla{islas.size()};
  vector<vertice<double>> representante(n_isla);

  double coste_min{GrafoP<double>::INFINITO}, coste_act;
  for (size_t i = 0; i < n_isla; ++i) {
    i_isla = islas[i][0];                    // Indice Inicio matriz isla[i]
    f_isla = islas[i][islas[i].size() - 1];  // Indicie fin matriz isla[i]
    for (size_t j = i_isla; j < f_isla; ++j) {
      coste_act = std::accumulate(floyd[j].begin() + i_isla,
                                  floyd[j].end() - (n_isla - f_isla), 0,
                                  SumNotInf<double>());
      if (coste_act < coste_min) {
        coste_min = coste_act;
        representante[i] = j;
      }
    }
  }
  return representante;
}
#endif