#ifndef ABIN_P1_HPP
#define ABIN_P1_HPP
#include "abin.hpp"
namespace Enlazada {
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
  return 1 + std::max(altura_r(a, a.hijoIzqdoB(n)),
                      altura_r(a, a.hijoDrchoB(n)));
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
  if (n == Abin<T>::NODO_NULO) {
    return true;
  }
  if (a.hijoIzqdoB(n) == Abin<T>::NODO_NULO &&
      a.hijoDrchoB(n) == Abin<T>::NODO_NULO) {
    return true;
  }
  if (a.hijoIzqdoB(n) && a.hijoDrchoB(n)) {
    return (isFullTree_r(a.hijoIzqdoB(n)) && isFullTree_r(a.hijoDrchoB(n)));
  }
  return false;
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
  return 1 + std::max(altura_r(a, a.hijoIzqdoB(n)),
                      altura_r(a, a.hijoDrchoB(n)));
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
  if (n == Abin<T>::NODO_NULO) {
    return true;
  }
  if (a.hijoIzqdoB(n) == Abin<T>::NODO_NULO &&
      a.hijoDrchoB(n) == Abin<T>::NODO_NULO) {
    return true;
  }
  if (a.hijoIzqdoB(n) && a.hijoDrchoB(n)) {
    return (isFullTree_r(a, a.hijoIzqdoB(n)) &&
            isFullTree_r(a, a.hijoDrchoB(n)));
  }
  return false;
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
  return isFullTree_r(a, a.raizB());
}

} // namespace Vectorial

#endif