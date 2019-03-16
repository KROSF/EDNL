#ifndef ABIN_P2_HPP
#define ABIN_P2_HPP
#include "abin.hpp"
#include "op.hpp"
namespace Enlazada {
template <typename T> using Nodo = typename Abin<T>::Nodo;
template <typename T>
bool similares(const Abin<T> &a, const Abin<T> &b, const Nodo<T> &na,
               const Nodo<T> &nb) {
  if (na == Abin<T>::NODO_NULO && nb == Abin<T>::NODO_NULO) {
    return true;
  } else if (na != Abin<T>::NODO_NULO && nb != Abin<T>::NODO_NULO) {
    return similares(a, b, a.hijoIzqdoB(na), b.hijoIzqdoB(nb)) &&
           similares(a, b, a.hijoDrchoB(na), b.hijoDrchoB(nb));
  }
  return false;
}

template <typename T> bool operator^(const Abin<T> &a, const Abin<T> &b) {
  if (a.arbolVacioB() && b.arbolVacioB()) {
    return true;
  } else if (!a.arbolVacioB() && !b.arbolVacioB()) {
    return similares(a, b, a.raizB(), b.raizB());
  }
  return false;
}

template <typename T>
void reflejo_r(Abin<T> &r, Nodo<T> nr, const Abin<T> &a, Nodo<T> na) {
  if (na != Abin<T>::NODO_NULO) {
    if (auto hizq = a.hijoIzqdoB(na); hizq != Abin<T>::NODO_NULO) {
      r.insertarHijoDrchoB(nr, a.elemento(hizq));
      reflejo_r(r, r.hijoDrchoB(nr), a, a.hijoIzqdoB(na));
    }
    if (auto hdch = a.hijoDrchoB(na); hdch != Abin<T>::NODO_NULO) {
      r.insertarHijoIzqdoB(nr, a.elemento(hdch));
      reflejo_r(r, r.hijoIzqdoB(nr), a, a.hijoDrchoB(na));
    }
  }
}

template <typename T> Abin<T> reflejo(const Abin<T> &a) {
  Abin<T> R;
  if (!a.arbolVacioB()) {
    R.insertarRaizB(a.elemento(a.raizB()));
    reflejo_r(R, R.raizB(), a, a.raizB());
  }
  return R;
}

double operacion_r(const Abin<Op> &a, const Nodo<Op> &n) {
  if (a.hijoIzqdoB(n) == Abin<Op>::NODO_NULO &&
      a.hijoDrchoB(n) == Abin<Op>::NODO_NULO) {
    return a.elemento(n).operando;
  }
  switch (a.elemento(n).operador) {
  case '+':
    return operacion_r(a, a.hijoIzqdoB(n)) + operacion_r(a, a.hijoDrchoB(n));
  case '-':
    return operacion_r(a, a.hijoIzqdoB(n)) - operacion_r(a, a.hijoDrchoB(n));
  case '*':
    return operacion_r(a, a.hijoIzqdoB(n)) * operacion_r(a, a.hijoDrchoB(n));
  case '/':
    return operacion_r(a, a.hijoIzqdoB(n)) / operacion_r(a, a.hijoDrchoB(n));
  }
}

double operacion(const Abin<Op> &a) { return operacion_r(a, a.raizB()); }

} // namespace Enlazada
#endif