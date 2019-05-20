#ifndef PRACTICAS_P7_HPP
#define PRACTICAS_P7_HPP

#include <algorithm>
#include <tuple>
#include "grafos/alg.hpp"

using grafos::Lista;
using grafos::matriz;
using grafos::pmc::GrafoP;
using grafos::pmc::alg::arista;
using grafos::pmc::alg::camino;
using grafos::pmc::alg::Dijkstra;
using grafos::pmc::alg::FloydMax;
using grafos::pmc::alg::tCamino;
using grafos::pmc::alg::vertice;
using std::size_t;

template <typename tCoste>
arista<tCoste> OtraVezUnGrafoSA(const GrafoP<tCoste>& G) {
  matriz<vertice<tCoste>> P;
  matriz<tCoste> F{FloydMax(G, P)};
  const size_t n = F.dimension();
  arista<tCoste> max_c(-1, -1, GrafoP<tCoste>::INFINITO * -1);
  for (vertice<tCoste> v = 0; v < n; ++v) {
    for (vertice<tCoste> w = 0; w < n; ++w) {
      if (F[v][w] > max_c.coste) {
        max_c = arista<tCoste>(v, w, F[v][w]);
      }
    }
  }
  return max_c;
}

template <typename tCoste>
std::tuple<tCoste, tCamino<tCoste>> Laberinto(
    size_t dim, const Lista<arista<tCoste>>& paredes, vertice<tCoste> inicio,
    vertice<tCoste> fin) {
  GrafoP<tCoste> L(dim * dim);
  for (vertice<tCoste> v = 0; v < dim * dim; ++v) {
    if (v < dim * (dim - 1)) {
      L[v][v + dim] = L[v + dim][v] = 1;
    }
    if (v % dim != dim - 1) {
      L[v][v + 1] = L[v + 1][v] = 1;
    }
  }
  for (auto it = paredes.primera(); it != paredes.fin();
       it = paredes.siguiente(it)) {
    const arista<tCoste>& p = paredes.elemento(it);
    L[p.orig][p.dest] = L[p.dest][p.orig] = GrafoP<tCoste>::INFINITO;
  }
  vector<vertice<tCoste>> P;
  vector<tCoste> D{Dijkstra(L, inicio, P)};
  return {D[fin], camino<tCoste>(inicio, fin, P)};
}

template <typename tCoste>
void Distribucion(vertice<tCoste> centro, size_t cantidad,
                  const GrafoP<tCoste>& G, const vector<tCoste>& capacidad,
                  const vector<tCoste>& subvencion) {
  const size_t n{G.numVert()};
  matriz<tCoste> A(n);
  for (vertice<tCoste> v = 0; v < n; ++v) {
    A[v] = G[v];
    for (vertice<tCoste> w = 0; w < n; ++w) {
      if (A[v][w] != GrafoP<tCoste>::INFINITO) {
        A[v][w] *= cantidad;
      }
    }
  }
}

template <typename C>
double CementosZuelandia(const GrafoP<C>& G, vertice<C> capital,
                         const vector<C>& diario) {
  vector<vertice<C>> P;
  vector<C> D{Dijkstra(G, capital, P)};
  vector<C> Dinv{DijkstraInv(G, capital, P)};
  double km{0};
  D[capital] = Dinv[capital] = 0;
  for (vertice<C> v = 0; v < D.size(); ++v) {
    km += ((Dinv[v] + D[v]) * diario[v]);
  }
  return km;
}
#endif