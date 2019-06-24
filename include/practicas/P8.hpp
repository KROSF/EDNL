#ifndef PRACTICAS_P8_HPP
#define PRACTICAS_P8_HPP

#include <cmath>
#include <map>
#include <numeric>
#include "grafos/alg.hpp"

using grafos::matriz;
using grafos::Particion;
using grafos::ma::Grafo;
using grafos::pmc::GrafoP;
using grafos::pmc::alg::arista;
using grafos::pmc::alg::Floyd;
using grafos::pmc::alg::KruskallMax;
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

vector<arista<double>> Tombuctu2(const vector<Ciudad>& ciudades,
                                 const Grafo& carreteras) {
  size_t n{ciudades.size()};
  Particion P{static_cast<int>(n)};
  GrafoP<double> G(n);
  int repre_1, repre_2;
  for (size_t v = 0; v < n; ++v) {
    repre_1 = P.encontrar(v);
    for (size_t w = v; w < n; ++w) {
      if (carreteras[v][w]) {
        repre_2 = P.encontrar(w);
        P.unir(repre_1, repre_2);
      }
      G[v][w] = G[w][v] = ciudades[v].distancia(ciudades[w]);
    }
  }
  std::map<int, vector<size_t>> islas;
  for (size_t i = 0; i < n; ++i) {
    islas[P.encontrar(i)].push_back(i);
  }
  matriz<vertice<double>> mP;
  matriz<double> floyd{Floyd(G, mP)};
  double coste_act, costes_min{GrafoP<double>::INFINITO};
  size_t n_islas = islas.size();
  vector<vertice<double>> repre(n_islas);
  int repre_i = 0;
  for (auto& isla : islas) {
    for (auto& ciudad : isla.second) {
      coste_act =
          std::accumulate(floyd[ciudad].begin(), floyd[ciudad].end(), 0);
      if (coste_act < costes_min) {
        costes_min = coste_act;
        repre[repre_i] = ciudad;
      }
    }
    ++repre_i;
  }
  vector<arista<double>> aerolinea;
  for (size_t i = 0; i < n_islas; ++i) {
    for (size_t j = i + 1; j < n_islas; ++j) {
      size_t a = repre[i], b = repre[j];
      aerolinea.push_back(
          arista<double>{a, b, ciudades[a].distancia(ciudades[b])});
    }
  }
  return aerolinea;
}

template <typename T>
vector<arista<T>> Emasajer(const GrafoP<T>& G) {
  GrafoP<T> K{KruskallMax(G)};
  vector<arista<T>> canales;
  size_t n = K.numVert();
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      if (K[i][j] != GrafoP<T>::INFINITO) {
        canales.push_back(arista<T>{i, j, K[i][j]});
      }
    }
  }
  return canales;
}

template <typename T>
T Reteuni3(const GrafoP<T>& pais) {
  matriz<vertice<T>> mP;
  matriz<T> floyd{Floyd(pais, mP)};
  T coste_min{GrafoP<T>::INFINITO}, coste_act;
  for (size_t i = 0; i < floyd.dimension(); ++i) {
    coste_act = accumulate(floyd[i].begin(), floyd[i].end(), 0, SumNotInf<T>());
    if (coste_act < coste_min) {
      coste_min = coste_act;
    }
  }
  return coste_min;
}
#endif