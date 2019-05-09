#include "agen.hpp"
#include <algorithm>
namespace Enlazada {

template <typename T> using Nodo = typename Agen<T>::Nodo;

template <typename T> int grado(const Agen<T> &a) {
  int grado{0};
  if (!a.arbolVacio()) {
    grado_r(a, a.raiz(), &grado);
  }
  return grado;
}

template <typename T> int hijos(const Agen<T> &a, Nodo<T> n) {
  int hijos{0};
  if (n != Agen<T>::NODO_NULO) {
    if (auto hijo{a.hijoIzqdo(n)}; hijo != Agen<T>::NODO_NULO) {
      ++hijos;
      while ((hijo = a.hermDrcho(hijo)) != Agen<T>::NODO_NULO) {
        ++hijos;
      }
    }
  }
  return hijos;
}

template <typename T> void grado_r(const Agen<T> &a, Nodo<T> n, int *max) {
  if (n != Agen<T>::NODO_NULO) {
    *max = std::max(*max, hijos(a, n));
    n = a.hijoIzqdo(n);
    while (n != Agen<T>::NODO_NULO) {
      grado_r(a, n, max);
      n = a.hermDrcho(n);
    }
  }
}

template <typename T> int profundidad(const Agen<T> &a, Nodo<T> n) {
  int profundidad{0};
  if (n == Agen<T>::NODO_NULO) {
    return profundidad;
  }
  while (n != Agen<T>::NODO_NULO) {
    ++profundidad;
    n = a.padre(n);
  }
  return profundidad - 1;
}

template <typename T> int shortestPath(const Agen<T> &a, Nodo<T> n) {
  int depth{0};
  if (n != Agen<T>::NODO_NULO) {
    n = a.hijoIzqdo(n);
    while (n != Agen<T>::NODO_NULO) {
      depth = std::min(shortestPath(a, n), depth) + 1;
      n = a.hermDrcho(n);
    }
  }
  return depth;
}

template <typename T> int longestPath(const Agen<T> &a, Nodo<T> n) {
  int depth{0};
  if (n != Agen<T>::NODO_NULO) {
    if (n = a.hijoIzqdo(n); n == Agen<T>::NODO_NULO) {
      return depth;
    }
    while (n != Agen<T>::NODO_NULO) {
      depth = std::max(longestPath(a, n), depth);
      n = a.hermDrcho(n);
    }
    return depth + 1;
  }
  return depth;
}

template <typename T> int desequilibrio(const Agen<T> &a) {
  return longestPath(a, a.raiz()) - shortestPath(a, a.raiz());
}

void destruirNodos(Agen<int> &a, Nodo<int> n) {
  if (n != Agen<int>::NODO_NULO) {
    Nodo<int> hijo{a.hijoIzqdo(n)};
    destruirNodos(a, hijo);
    while (hijo != Agen<int>::NODO_NULO) {
      if (a.hijoIzqdo(hijo) != Agen<int>::NODO_NULO) {
        destruirNodos(a, hijo);
      }
      a.eliminarHijoIzqdo(n);
      hijo = a.hijoIzqdo(n);
    }
  }
}

void poda_r(Agen<int> &a, Nodo<int> n, int x) {
  if (n != Agen<int>::NODO_NULO) {
    if (a.elemento(n) == x) {
      destruirNodos(a, n);
    } else {
      n = a.hijoIzqdo(n);
      while (n != Agen<int>::NODO_NULO) {
        poda_r(a, n, x);
        n = a.hermDrcho(n);
      }
    }
  }
}

void poda(Agen<int> &a, int x) { poda_r(a, a.raiz(), x); }

} // namespace Enlazada