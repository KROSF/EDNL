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
std::tuple<size_t, size_t> diametro(const GrafoP<tCoste>& G) {
  matriz<vertice<tCoste>> P;
  matriz<tCoste> F{Floyd(G, P)};
  size_t n{F.dimension()};
  vector<size_t> diam(n, 0);
  for (size_t i = 0, max = 0, max2 = 0; i < n; ++i, max = max2 = 0) {
    for (size_t j = 0; j < n; ++j) {
      if (F[i][j] != GrafoP<tCoste>::INFINITO) {
        if (static_cast<size_t>(F[i][j]) > max && max <= max2) {
          max = F[i][j];
        } else if (static_cast<size_t>(F[i][j]) > max2) {
          max2 = F[i][j];
        }
      }
    }
    diam[i] = max + max2;
  }
  auto v = std::min_element(diam.begin(), diam.end());
  return {std::distance(diam.begin(), v), *v};
}

template <typename tCoste>
size_t Diametro(const GrafoP<tCoste>& G) {
  auto [_, diam] = diametro(G);
  return diam;
}

template <typename tCoste>
size_t PseudoCentro(const GrafoP<tCoste>& G) {
  auto [nodo, _] = diametro(G);
  return nodo;
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
        tCoste ikj = suma(A[i][k], A[k][j]);
        if (ikj < A[i][j]) {
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
      MCZ[v][w] = ((v == w) ? suma(D[w], Dinv[v]) : GrafoP<tCoste>::INFINITO);
    }
  }
  return MCZ;
}
#endif