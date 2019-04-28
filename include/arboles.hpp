#ifndef ARBOLES_HPP
#define ARBOLES_HPP
#include "agen.hpp"
namespace Enlazada {
template <typename T> using Nodo = typename Agen<T>::Nodo;

template <typename T> bool esTernario(const Agen<T> &a) {
  return ternario_r(a, a.raiz());
}

template <typename T> bool ternario_r(const Agen<T> &a, Nodo<T> n) {
  bool ter{true};
  if (n != Agen<T>::NODO_NULO) {
    int n_h = hijos(a, n);
    ter = (n_h == 3 || n_h == 0) ? true : false;
    n = a.hijoIzqdo(n);
    while (n != Agen<T>::NODO_NULO && ter) {
      ter = ternario_r(a, n);
      n = a.hermDrcho(n);
    }
  }
  return ter;
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
} // namespace Enlazada
#endif