#ifndef PRACTICAS_P6_HPP
#define PRACTICAS_P6_HPP

#include <algorithm>
#include "grafos/alg.hpp"

using grafos::matriz;
using grafos::pmc::GrafoP;
using grafos::pmc::alg::arista;
using grafos::pmc::alg::Dijkstra;
using grafos::pmc::alg::DijkstraInv;
using grafos::pmc::alg::Floyd;
using grafos::pmc::alg::suma;
using grafos::pmc::alg::vertice;
using std::size_t;
using std::vector;

template <typename tCoste>
std::tuple<std::tuple<tCoste, tCoste>, std::tuple<tCoste, tCoste>>
TwoHighestValues(const vector<tCoste>& row,
                 tCoste ignore = GrafoP<tCoste>::INFINITO) {
  std::tuple<tCoste, tCoste> actual{ignore, 0}, anterior{ignore, 0};
  for (tCoste i = 0; i < row.size(); ++i) {
    if (row[i] != ignore) {
      if (std::get<1>(actual) < row[i]) {
        anterior = actual;
        actual = std::make_tuple(i, row[i]);
      } else if (std::get<1>(actual) > row[i] &&
                 row[i] > std::get<1>(anterior)) {
        anterior = std::make_tuple(i, row[i]);
      }
    }
  }
  return {actual, anterior};
}

template <typename T>
std::tuple<T, T> pseudoCentroDiametro(const GrafoP<T>& G) {
  matriz<vertice<T>> P;
  matriz<T> F{Floyd(G, P)};
  size_t n{F.dimension()};
  vector<size_t> diam(n, 0);
  for (size_t i = 0; i < n; ++i) {
    const auto& [max_a, max_b] = TwoHighestValues<T>(F[i]);
    if (std::get<0>(max_b) == GrafoP<T>::INFINITO ||
        std::get<0>(max_a) == GrafoP<T>::INFINITO) {
      diam[i] = GrafoP<T>::INFINITO;
    } else {
      diam[i] = std::get<1>(max_a) + std::get<1>(max_b);
    }
  }
  auto nodo = std::min_element(diam.begin(), diam.end());
  return {std::distance(diam.begin(), nodo), *nodo};
}

template <typename tCoste>
size_t PseudoCentro(const GrafoP<tCoste>& G) {
  auto [nodo, _] = pseudoCentroDiametro(G);
  return nodo;
}

template <typename tCoste>
size_t Diametro(const GrafoP<tCoste>& G) {
  auto [_, diam] = pseudoCentroDiametro(G);
  return diam;
}

template <typename tCoste>
bool esAciclico(const GrafoP<tCoste>& G) {
  bool ciclo{true};
  const size_t n = G.numVert();
  matriz<tCoste> A(n);
  for (vertice<tCoste> i = 0; i < n; ++i) {
    A[i] = G[i];
  }
  for (vertice<tCoste> k = 0; k < n; ++k) {
    for (vertice<tCoste> i = 0; i < n; ++i) {
      for (vertice<tCoste> j = 0; j < n; ++j) {
        if (tCoste ikj = suma(A[i][k], A[k][j]); ikj < A[i][j]) {
          A[i][j] = ikj;
        }
      }
    }
  }
  for (size_t i = 0; i < n && ciclo; ++i) {
    ciclo = A[i][i] == GrafoP<tCoste>::INFINITO;
  }
  return ciclo;
}

template <typename tCoste>
matriz<tCoste> Zuelandia(const GrafoP<tCoste>& G,
                         const vector<tCoste>& ciudades,
                         const vector<arista<tCoste>>& caminos,
                         vertice<tCoste> capital) {
  GrafoP<tCoste> Z{G};
  vector<vertice<tCoste>> P;
  const size_t n{G.numVert()};
  for (size_t i = 0; i < n; ++i) {
    for (const auto& c : ciudades) {
      Z[i][c] = GrafoP<tCoste>::INFINITO;
    }
  }
  for (const auto& c : caminos) {
    Z[c.orig][c.dest] = GrafoP<tCoste>::INFINITO;
  }
  matriz<tCoste> MCZ(n);
  vector<tCoste> D{Dijkstra(Z, capital, P)}, Dinv{DijkstraInv(Z, capital, P)};
  for (vertice<tCoste> v = 0; v < n; ++v) {
    for (vertice<tCoste> w = 0; w < n; ++w) {
      MCZ[v][w] = ((v == w) ? 0 : suma(D[w], Dinv[v]));
    }
  }
  for (const auto& c : ciudades) {
    MCZ[c][c] = GrafoP<tCoste>::INFINITO;
  }
  return MCZ;
}
#endif