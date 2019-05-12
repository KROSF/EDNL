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
      if (static_cast<size_t>(F[i][j]) > max && max <= max2) {
        max = F[i][j];
      } else if (static_cast<size_t>(F[i][j]) > max2) {
        max2 = F[i][j];
      }
    }
    diam.push_back(max + max2);
  }
  auto v = std::min_element(diam.begin(), diam.end());
  return {std::distance(diam.begin(), v), *v};
}

template <typename T>
size_t Diametro(const GrafoP<T>& G) {
  auto [_, diam] = diametro(G);
  return diam;
}

template <typename T>
size_t PseudoCentro(const GrafoP<T>& G) {
  auto [nodo, _] = diametro(G);
  return nodo;
}

template <typename T>
bool esAciclico(const GrafoP<T>& G) {
  bool ciclo{true};
  const size_t n = G.numVert();
  matriz<T> A(n);
  for (vertice<T> i = 0; i < n; ++i) {
    A[i] = G[i];
  }
  for (vertice<T> k = 0; k < n; ++k) {
    for (vertice<T> i = 0; i < n; ++i) {
      for (vertice<T> j = 0; j < n; ++j) {
        T ikj = suma(A[i][k], A[k][j]);
        if (ikj < A[i][j]) {
          A[i][j] = ikj;
        }
      }
    }
  }
  for (size_t i = 0; i < n && ciclo; ++i) {
    ciclo = A[i][i] == GrafoP<T>::INFINITO;
  }
  return ciclo;
}

template <typename T>
matriz<T> Zuelandia(const GrafoP<T>& G, const vector<T>& ciudades,
                    const vector<arista<T>>& caminos, vertice<T> capital) {
  GrafoP<T> Z{G};
  vector<vertice<T>> P;
  const size_t n{G.numVert()};
  for (size_t i = 0; i < n; ++i) {
    for (const auto& c : ciudades) {
      Z[i][c] = GrafoP<T>::INFINITO;
    }
  }
  for (const auto& c : caminos) {
    Z[c.orig][c.dest] = GrafoP<T>::INFINITO;
  }
  matriz<T> MCZ(n);
  vector<T> D{Dijkstra(Z, capital, P)}, Dinv{DijkstraInv(Z, capital, P)};
  for (vertice<T> v = 0; v < n; ++v) {
    for (vertice<T> w = 0; w < n; ++w) {
      MCZ[v][w] = ((v == W) ? suma(D[w], Dinv[v]) : GrafoP<T>::INFINITO);
    }
  }
  return MCZ;
}
#endif