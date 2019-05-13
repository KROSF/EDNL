#ifndef GRAFOS_ALG_HPP
#define GRAFOS_ALG_HPP
#include <cassert>
#include "grafos/apo.hpp"
#include "grafos/cola.hpp"
#include "grafos/matriz.hpp"
#include "grafos/particion.hpp"
#include "grafos/pila.hpp"
#include "grafos/pla.hpp"
#include "grafos/pmc.hpp"
namespace grafos {
namespace pmc::alg {

template <typename T>
using vertice = typename GrafoP<T>::vertice;

template <typename T>
using tCamino = typename GrafoP<T>::tCamino;

template <typename T>
using arista = typename GrafoP<T>::arista;

template <typename T>
/**
 * Suma de costes. Devuelve GrafoP<tCoste>::INFINITO si alguno de los
 * dos parámetros vale GrafoP<tCoste>::INFINITO.
 */
T suma(T x, T y) {
  const T INFINITO = GrafoP<T>::INFINITO;
  if (x == INFINITO || y == INFINITO)
    return INFINITO;
  else
    return x + y;
}

template <typename tCoste>
/**
 * Calcula los caminos de coste mínimo entre origen y todos los
 * vértices del grafo G. Devuelve un vector de tamaño G.numVert()
 * con estos costes mínimos y un vector P, también de tamaño
 * G.numVert(), tal que P[i] es el último vértice del camino de
 * coste mínimo de origen a i.
 */
vector<tCoste> Dijkstra(const GrafoP<tCoste>& G, vertice<tCoste> origen,
                        vector<vertice<tCoste>>& P) {
  vertice<tCoste> v, w;
  const std::size_t n = G.numVert();
  vector<bool> S(n, false);
  vector<tCoste> D;
  D = G[origen];
  D[origen] = 0;
  P = vector<vertice<tCoste>>(n, origen);
  S[origen] = true;
  for (std::size_t i = 1; i <= n - 2; ++i) {
    tCoste costeMin = GrafoP<tCoste>::INFINITO;
    for (v = 0; v < n; ++v) {
      if (!S[v] && D[v] <= costeMin) {
        costeMin = D[v];
        w = v;
      }
    }
    S[w] = true;
    for (v = 0; v < n; v++) {
      if (!S[v]) {
        tCoste Owv = suma(D[w], G[w][v]);
        if (Owv < D[v]) {
          D[v] = Owv;
          P[v] = w;
        }
      }
    }
  }
  return D;
}

template <typename tCoste>
/**
 * Dijkstra Inverso
 */
vector<tCoste> DijkstraInv(const GrafoP<tCoste>& G, vertice<tCoste> destino,
                           vector<vertice<tCoste>>& P) {
  vertice<tCoste> v, w;
  const std::size_t n = G.numVert();
  vector<bool> S(n, false);
  vector<tCoste> D(n);
  for (vertice<tCoste> i = 0; i < n; ++i) {
    D[i] = G[i][destino];
  }
  D[destino] = 0;
  S[destino] = true;
  P = vector<vertice<tCoste>>(n, destino);
  for (size_t i = 1; i < n - 2; ++i) {
    tCoste min = GrafoP<tCoste>::INFINITO;
    for (v = 0; v < n - 1; ++v) {
      if (!S[v] && min >= D[v]) {
        min = D[v];
        w = v;
      }
    }
    S[w] = true;
    for (v = 0; v < n - 1; ++v) {
      if (!S[v]) {
        tCoste coste = suma(G[v][w], D[w]);
        if (coste < D[v]) {
          D[v] = coste;
          P[v] = w;
        }
      }
    }
  }
  return D;
}

template <typename T>
/**
 * Devuelve el camino de coste mínimo entre los vértices orig  y v
 * a partir de un vector P obtenido mediante la función Dijkstra().
 */
tCamino<T> camino(vertice<T> orig, vertice<T> v, const vector<vertice<T>>& P) {
  tCamino<T> C;
  C.insertar(v, C.primera());
  do {
    C.insertar(P[v], C.primera());
    v = P[v];
  } while (v != orig);
  return C;
}

template <typename tCoste>
/**  Calcula los caminos de coste mínimo entre cada par de vértices
 * del grafo G. Devuelve una matriz de costes mínimos de tamaño
 * n x n, con n = G.numVert(), y una matriz de vértices P de
 * tamaño n x n, tal que P[i][j] es el vértice por el que pasa el
 * camino de coste mínimo de i a j, si este vértice es i el camino
 * es directo.
 */
matriz<tCoste> Floyd(const GrafoP<tCoste>& G, matriz<vertice<tCoste>>& P) {
  const std::size_t n = G.numVert();
  matriz<tCoste> A(n);
  P = matriz<vertice<tCoste>>(n, -1);
  for (vertice<tCoste> i = 0; i < n; ++i) {
    A[i] = G[i];
    A[i][i] = 0;
    for (vertice<tCoste> j = 0; j < n; ++j) {
      if (G[i][j] != GrafoP<tCoste>::INFINITO) {
        P[i][j] = i;
      }
    }
  }

  for (vertice<tCoste> k = 0; k < n; ++k) {
    for (vertice<tCoste> i = 0; i < n; ++i) {
      for (vertice<tCoste> j = 0; j < n; ++j) {
        if (tCoste ikj = suma(A[i][k], A[k][j]); ikj < A[i][j]) {
          A[i][j] = ikj;
          P[i][j] = P[k][j];
        }
      }
    }
  }
  return A;
}

template <typename tCoste>
matriz<tCoste> FloydMax(const GrafoP<tCoste>& G, matriz<vertice<tCoste>>& P) {
  const std::size_t n = G.numVert();
  matriz<tCoste> A(n);
  P = matriz<vertice<tCoste>>(n, -1);
  for (vertice<tCoste> i = 0; i < n; ++i) {
    A[i] = G[i];
    A[i][i] = 0;
    for (vertice<tCoste> j = 0; j < n; ++j) {
      if (G[i][j] != GrafoP<tCoste>::INFINITO) {
        P[i][j] = i;
      }
    }
  }
  for (vertice<tCoste> k = 0; k < n; ++k) {
    for (vertice<tCoste> i = 0; i < n; ++i) {
      for (vertice<tCoste> j = 0; j < n; ++j) {
        if (tCoste ikj = suma(A[i][k], A[k][j]);
            ikj != GrafoP<tCoste>::INFINITO && ikj > A[i][j]) {
          A[i][j] = ikj;
          P[i][j] = P[k][j];
        }
      }
    }
  }
  return A;
}

template <typename tCoste>
tCamino<tCoste> caminoAux(vertice<tCoste> v, vertice<tCoste> w,
                          const matriz<vertice<tCoste>>& P) {
  tCamino<tCoste> C1, C2;
  vertice<tCoste> u = P[v][w];
  if (u != v) {
    C1 = caminoAux<tCoste>(v, u, P);
    C1.insertar(u, C1.fin());
    C2 = caminoAux<tCoste>(u, w, P);
    C1 += C2;
  }
  return C1;
}

template <typename tCoste>
/**
 * Devuelve el camino de coste mínimo desde i hasta j a partir
 * de una matriz P obtenida mediante la función Floyd().
 */
tCamino<tCoste> camino(vertice<tCoste> v, vertice<tCoste> w,
                       const matriz<vertice<tCoste>>& P) {
  tCamino<tCoste> C = caminoAux<tCoste>(v, w, P);
  C.insertar(v, C.primera());
  C.insertar(w, C.fin());
  return C;
}

template <typename tCoste>
/**
 * Devuelve un árbol generador de coste mínimo
 * de un grafo no dirigido ponderado y conexo G.
 */
GrafoP<tCoste> Prim(const GrafoP<tCoste>& G) {
  assert(!G.esDirigido());
  const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
  arista<tCoste> a;
  const std::size_t n = G.numVert();
  GrafoP<tCoste> g(n);
  vector<bool> U(n, false);
  Apo<arista<tCoste>> A(n * (n - 1) / 2 - n + 2);
  U[0] = true;
  for (vertice<tCoste> v = 1; v < n; ++v)
    if (G[0][v] != INFINITO) A.insertar(arista<tCoste>(0, v, G[0][v]));
  for (std::size_t i = 1; i <= n - 1; ++i) {
    do {
      a = A.cima();
      A.suprimir();
    } while (U[a.dest]);
    g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste;
    vertice<tCoste> u = a.dest;
    U[u] = true;
    for (vertice<tCoste> v = 0; v < n; ++v)
      if (!U[v] && G[u][v] != INFINITO)
        A.insertar(arista<tCoste>(u, v, G[u][v]));
  }
  return g;
}

template <typename tCoste>
/**
 * Devuelve un árbol generador de coste mínimo
 * de un grafo no dirigido ponderado y conexo G.
 */
GrafoP<tCoste> Kruskall(const GrafoP<tCoste>& G) {
  assert(!G.esDirigido());
  const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
  const std::size_t n = G.numVert();
  GrafoP<tCoste> g(n);
  Particion P(n);
  Apo<arista<tCoste>> A(n * n);
  for (vertice<tCoste> u = 0; u < n; ++u)
    for (vertice<tCoste> v = u + 1; v < n; ++v)
      if (G[u][v] != INFINITO) A.insertar(arista<tCoste>(u, v, G[u][v]));
  std::size_t i = 1;
  while (i <= n - 1) {
    arista<tCoste> a = A.cima();
    A.suprimir();
    vertice<tCoste> u = P.encontrar(a.orig);
    vertice<tCoste> v = P.encontrar(a.dest);
    if (u != v) {
      P.unir(u, v);
      g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste;
      i++;
    }
  }
  return g;
}

}  // namespace pmc::alg
namespace ma::alg {
using vertice = Grafo::vertice;
enum visitas { NO_VISITADO, VISITADO };
matriz<bool> Warshall(const Grafo& G) {
  const std::size_t n = G.numVert();
  matriz<bool> A(n);
  for (vertice i = 0; i < n; ++i) {
    A[i] = G[i];
    A[i][i] = true;
  }
  for (vertice k = 0; k < n; ++k)
    for (vertice i = 0; i < n; ++i)
      for (vertice j = 0; j < n; ++j)
        if (!A[i][j]) A[i][j] = A[i][k] && A[k][j];
  return A;
}

static Lista<vertice> Profun(const Grafo& G, vertice v,
                             vector<visitas>& marcas) {
  const std::size_t n = G.numVert();
  Lista<vertice> Lv;

  marcas[v] = VISITADO;
  Lv.insertar(v, Lv.fin());
  for (vertice w = 0; w < n; ++w)
    if (G[v][w] && marcas[w] == NO_VISITADO) Lv += Profun(G, w, marcas);
  return Lv;
}

Lista<vertice> Profundidad(const Grafo& G, vertice v) {
  const std::size_t n = G.numVert();
  vector<visitas> marcas(n, NO_VISITADO);
  Lista<vertice> Lv;
  vertice i = v;

  do {
    if (marcas[i] == NO_VISITADO) Lv += Profun(G, i, marcas);
    i = (i + 1) % n;
  } while (i != v);
  return Lv;
}

Lista<vertice> Profundidad2(const Grafo& G, vertice u) {
  const std::size_t n = G.numVert();
  vector<visitas> marcas(n, NO_VISITADO);
  Pila<vertice> P;
  Lista<vertice> Lv;
  vertice i = u;
  do {
    if (marcas[i] == NO_VISITADO) {
      P.push(i);
      do {
        vertice v = P.tope();
        P.pop();
        if (marcas[v] == NO_VISITADO) {
          marcas[v] = VISITADO;
          Lv.insertar(v, Lv.fin());
          for (vertice w = n; w > 0; --w)
            if (G[v][w - 1] && marcas[w - 1] == NO_VISITADO) P.push(w - 1);
        }
      } while (!P.vacia());
    }
    i = (i + 1) % n;
  } while (i != u);
  return Lv;
}

Lista<vertice> Anchura(const Grafo& G, vertice u) {
  const std::size_t n = G.numVert();
  vector<visitas> marcas(n, NO_VISITADO);
  Cola<vertice> C;
  Lista<vertice> Lv;
  vertice i = u;
  do {
    if (marcas[i] == NO_VISITADO) {
      C.push(i);
      do {
        vertice v = C.frente();
        C.pop();
        if (marcas[v] == NO_VISITADO) {
          marcas[v] = VISITADO;
          Lv.insertar(v, Lv.fin());
          for (vertice w = n; w > 0; --w)
            if (G[v][w - 1] && marcas[w - 1] == NO_VISITADO) C.push(w - 1);
        }
      } while (!C.vacia());
    }
    i = (i + 1) % n;
  } while (i != u);
  return Lv;
}

}  // namespace ma::alg
}  // namespace grafos
#endif