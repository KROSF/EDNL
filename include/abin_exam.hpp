#ifndef ABIN_EXAM_HPP
#define ABIN_EXAM_HPP
#include "abin.hpp"
#include <algorithm>
#include <array>
namespace Enlazada {
template <typename T> using Nodo = typename Abin<T>::Nodo;

template <typename T> bool tieneNietos(const Abin<T> &a, const Nodo<T> &n) {
  auto h_izq = a.hijoIzqdoB(n);
  auto h_dch = a.hijoDrchoB(n);
  if (h_izq != Abin<T>::NODO_NULO && h_dch != Abin<T>::NODO_NULO) {
    std::array<bool, 4> nietos{a.hijoIzqdoB(h_izq) != Abin<T>::NODO_NULO,
                               a.hijoDrchoB(h_izq) != Abin<T>::NODO_NULO,
                               a.hijoIzqdoB(h_dch) != Abin<T>::NODO_NULO,
                               a.hijoDrchoB(h_dch) != Abin<T>::NODO_NULO};
    return std::count(nietos.begin(), nietos.end(), true) == 3;
  }
  return false;
}

template <typename T> int nietos_r(const Abin<T> &a, const Nodo<T> &n) {
  if (n == Abin<T>::NODO_NULO) {
    return 0;
  }
  if (tieneNietos(a, n)) {
    return 1 + nietos_r(a, a.hijoIzqdoB(n)) + nietos_r(a, a.hijoDrchoB(n));
  }
  return nietos_r(a, a.hijoIzqdoB(n)) + nietos_r(a, a.hijoDrchoB(n));
}

template <typename T>
bool primos(const Abin<T> &a, const Nodo<T> &pl, const Nodo<T> &pr) {
  if (pl != Abin<T>::NODO_NULO && pr != Abin<T>::NODO_NULO) {
    auto padre_pl = a.padreB(pr);
    auto padre_pr = a.padreB(pl);
    if (padre_pl != Abin<T>::NODO_NULO && padre_pr != Abin<T>::NODO_NULO) {
      auto abuelo_pl = a.padreB(padre_pl);
      auto abuelo_pr = a.padreB(padre_pr);
      if (abuelo_pl != Abin<T>::NODO_NULO && abuelo_pr != Abin<T>::NODO_NULO) {
        return abuelo_pl == abuelo_pr && padre_pl != padre_pr;
      }
    }
  }
  return false;
}

template <typename T> bool rebelde(const Abin<T> &a, Nodo<T> n) {
  unsigned tipo1{0}, tipo2{0};
  T elemento{a.elemento(n)};
  while (n != Abin<T>::NODO_NULO) {
    if (a.elemento(n) == elemento) {
      ++tipo1;
    } else {
      ++tipo2;
    }
    n = a.padreB(n);
  }
  return tipo1 < tipo2;
}

template <typename T> int rebeldes(const Abin<T> &a, Nodo<T> n) {
  if (n == Abin<T>::NODO_NULO) {
    return 0;
  }
  if (rebelde(a, n)) {
    return 1 + rebeldes(a, a.hijoIzqdoB(n)) + rebeldes(a, a.hijoDrchoB(n));
  }
  return rebeldes(a, a.hijoIzqdoB(n)) + rebeldes(a, a.hijoDrchoB(n));
}

template <typename T> bool isComplete(const Abin<T> &a, Nodo<T> n) {
  return a.hijoIzqdoB(n) != Abin<T>::NODO_NULO &&
         a.hijoDrchoB(n) != Abin<T>::NODO_NULO;
}

template <typename T> void destroy(Abin<T> &a, Nodo<T> n, bool isLeft) {
  if (n != Abin<T>::NODO_NULO) {
    destroy(a, a.hijoIzqdoB(n), true);
    destroy(a, a.hijoDrchoB(n), false);
    if (isLeft) {
      a.eliminarHijoIzqdoB(a.padreB(n));
    } else {
      a.eliminarHijoDrchoB(a.padreB(n));
    }
  }
}

template <typename T> void transformar_r(Abin<T> &a, Nodo<T> n) {
  if (n != Abin<T>::NODO_NULO) {
    if (!isComplete(a, n)) {
      if (a.hijoIzqdoB(n) != Abin<T>::NODO_NULO) {
        destroy(a, a.hijoIzqdoB(n), true);
      } else {
        destroy(a, a.hijoDrchoB(n), false);
      }
    } else {
      transformar_r(a, a.hijoIzqdoB(n));
      transformar_r(a, a.hijoDrchoB(n));
    }
  }
}

template <typename T> void transformar(Abin<T> &a) {
  transformar_r(a, a.raizB());
}

} // namespace Enlazada
#endif