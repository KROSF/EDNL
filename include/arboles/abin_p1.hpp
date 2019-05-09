#ifndef ABIN_P1_HPP
#define ABIN_P1_HPP
#include "abin.hpp"
namespace Enlazada {
template <typename T> using Nodo = typename Abin<T>::Nodo;

template <typename T>
void nodos_r(const Abin<T> &a, const Nodo<T> &n, int &nodos) {
  if (n != Abin<T>::NODO_NULO) {
    ++nodos;
    nodos_r(a, a.hijoIzqdoB(n), nodos);
    nodos_r(a, a.hijoDrchoB(n), nodos);
  }
}

template <typename T> int altura_r(const Abin<T> &a, const Nodo<T> &n) {
  if (n == Abin<T>::NODO_NULO) {
    return -1;
  }
  return 1 +
         std::max(altura_r(a, a.hijoIzqdoB(n)), altura_r(a, a.hijoDrchoB(n)));
}

template <typename T> int desequilibrio_r(const Abin<T> &a, const Nodo<T> &n) {
  if (n == Abin<T>::NODO_NULO) {
    return 0;
  }
  return std::max(
      {std::abs(a.altura(a.hijoIzqdoB(n)) - a.altura(a.hijoDrchoB(n))),
       desequilibrio_r(a, a.hijoIzqdoB(n)),
       desequilibrio_r(a, a.hijoDrchoB(n))});
}

template <typename T> bool isFullTree_r(const Abin<T> &a, const Nodo<T> &n) {
  if (a.altura(a.raizB()) - 1 == a.profundidad(n)) {
    bool h_izq = a.hijoIzqdoB(n) == Abin<T>::NODO_NULO;
    bool h_dch = a.hijoDrchoB(n) == Abin<T>::NODO_NULO;
    if (h_izq && h_dch) {
      return true;
    } else if (!h_izq && !h_dch) {
      return true;
    }
    return false;
  } else if (a.altura(a.hijoDrchoB(n)) > a.altura(a.hijoIzqdoB(n))) {
    return isFullTree_r(a, a.hijoDrchoB(n));
  } else if (a.altura(a.hijoDrchoB(n)) < a.altura(a.hijoIzqdoB(n))) {
    return isFullTree_r(a, a.hijoIzqdoB(n));
  }
  return isFullTree_r(a, a.hijoDrchoB(n)) && isFullTree_r(a, a.hijoIzqdoB(n));
}

template <typename T> int nodos(const Abin<T> &a) {
  int n = 0;
  nodos_r(a, a.raizB(), n);
  return n;
}

template <typename T> int altura(const Abin<T> &a) {
  return altura_r(a, a.raizB());
}

template <typename T> int profundidad(const Abin<T> &a, const Nodo<T> &n) {
  if (a.padreB(n) == Abin<T>::NODO_NULO) {
    return 0;
  }
  return 1 + profundidad(a, a.padreB(n));
}

template <typename T> int desequilibrio(const Abin<T> &a) {
  return desequilibrio_r(a, a.raizB());
}

template <typename T> bool isFullTree(const Abin<T> &a) {
  if (a.arbolVacioB()) {
    return false;
  }
  return isFullTree_r(a, a.raizB());
}

} // namespace Enlazada

namespace Vectorial {
template <typename T> using Nodo = typename Abin<T>::Nodo;

template <typename T> int nodos_r(const Abin<T> &a, const Nodo<T> &n) {
  if (n == Abin<T>::NODO_NULO) {
    return 0;
  }
  return 1 + nodos_r(a, a.hijoIzqdoB(n)) + nodos_r(a, a.hijoDrchoB(n));
}

template <typename T> int altura_r(const Abin<T> &a, const Nodo<T> &n) {
  if (n == Abin<T>::NODO_NULO) {
    return -1;
  }
  return 1 +
         std::max(altura_r(a, a.hijoIzqdoB(n)), altura_r(a, a.hijoDrchoB(n)));
}

template <typename T> int desequilibrio_r(const Abin<T> &a, const Nodo<T> &n) {
  if (n == Abin<T>::NODO_NULO) {
    return 0;
  }
  return std::max(
      {std::abs(a.altura(a.hijoIzqdoB(n)) - a.altura(a.hijoDrchoB(n))),
       desequilibrio_r(a, a.hijoIzqdoB(n)),
       desequilibrio_r(a, a.hijoDrchoB(n))});
}

template <typename T> bool isFullTree_r(const Abin<T> &a, const Nodo<T> &n) {
  if (a.altura(a.raizB()) - 1 == a.profundidad(n)) {
    bool h_izq = a.hijoIzqdoB(n) == Abin<T>::NODO_NULO;
    bool h_dch = a.hijoDrchoB(n) == Abin<T>::NODO_NULO;
    if (h_izq && h_dch) {
      return true;
    } else if (!h_izq && !h_dch) {
      return true;
    }
    return false;
  } else if (a.altura(a.hijoDrchoB(n)) > a.altura(a.hijoIzqdoB(n))) {
    return isFullTree_r(a, a.hijoDrchoB(n));
  } else if (a.altura(a.hijoDrchoB(n)) < a.altura(a.hijoIzqdoB(n))) {
    return isFullTree_r(a, a.hijoIzqdoB(n));
  }
  return isFullTree_r(a, a.hijoDrchoB(n)) && isFullTree_r(a, a.hijoIzqdoB(n));
}

template <typename T> int nodos(const Abin<T> &a) {
  return nodos_r(a, a.raizB());
}

template <typename T> int altura(const Abin<T> &a) {
  return altura_r(a, a.raizB());
}

template <typename T> int profundidad(const Abin<T> &a, const Nodo<T> &n) {
  if (a.padreB(n) == Abin<T>::NODO_NULO) {
    return 0;
  }
  return 1 + profundidad(a, a.padreB(n));
}

template <typename T> int desequilibrio(const Abin<T> &a) {
  return desequilibrio_r(a, a.raizB());
}

template <typename T> bool isFullTree(const Abin<T> &a) {
  if (a.arbolVacioB()) {
    return false;
  }
  return isFullTree_r(a, a.raizB());
}

} // namespace Vectorial

#endif