#ifndef ABB_PX_HPP
#define ABB_PX_HPP
#include "abb.hpp"
#include <algorithm>
#include <functional>
#include <vector>

template <typename T>
void inOrder(const Abb<T> &a, std::function<void(const Abb<T> &)> func) {
  if (!a.vacio()) {
    inOrder(a.izquierdo(), func);
    func(a);
    inOrder(a.derecho(), func);
  }
}

template <typename T> void equilibrar(Abb<T> &a) {
  if (!a.vacio()) {
    std::vector<T> v;
    inOrder<T>(a, [&v](const Abb<T> &e) { v.push_back(e.elemento()); });
    a.~Abb();
    equilibrar_r(a, v, v.size(), 0);
  }
}

template <typename T>
void equilibrar_r(Abb<T> &a, std::vector<T> &v, int n, int ini) {
  if (ini != n) {
    int pos{((n - ini) / 2) + ini};
    a.insertar(v[pos]);
    equilibrar_r(a, v, pos, ini);
    equilibrar_r(a, v, n, pos + 1);
  }
}

template <typename T> void union_r(const Abb<T> &a, Abb<T> &unio) {
  if (!a.vacio()) {
    unio.insertar(a.elemento());
    union_r(a.izquierdo(), unio);
    union_r(a.derecho(), unio);
  }
}

template <typename T> Abb<T> unionAbb(const Abb<T> &a, const Abb<T> &b) {
  Abb<T> unio{a};
  union_r(b, unio);
  equilibrar(unio);
  return unio;
}

template <typename T>
void interseccion_r(const Abb<T> &a, const Abb<T> &b, Abb<T> &inter) {
  if (!a.vacio() && !b.vacio()) {
    if (!a.buscar(b.elemento()).vacio()) {
      inter.insertar(b.elemento());
    }
    interseccion_r(a, b.izquierdo(), inter);
    interseccion_r(a, b.derecho(), inter);
  }
}

template <typename T> Abb<T> interseccionAbb(const Abb<T> &a, const Abb<T> &b) {
  Abb<T> interseccion;
  interseccion_r(a, b, interseccion);
  equilibrar(interseccion);
  return interseccion;
}

template <typename T>
void diferencia_r(const Abb<T> &a, const Abb<T> &b, Abb<T> &diff) {
  if (!a.vacio()) {
    if (b.buscar(a.elemento()).vacio()) {
      diff.insertar(a.elemento());
    }
    diferencia_r(a.izquierdo(), b, diff);
    diferencia_r(a.derecho(), b, diff);
  }
}

template <typename T> Abb<T> diferenciaAbb(const Abb<T> &a, const Abb<T> &b) {
  Abb<T> diff;
  diferencia_r(a, b, diff);
  equilibrar(diff);
  return diff;
}

template <typename T> Abb<T> operadorRombo(const Abb<T> &a, const Abb<T> &b) {
  auto unio = unionAbb(a, b);
  auto inter = interseccionAbb(a, b);
  Abb<T> diff;
  diferencia_r(unio, inter, diff);
  equilibrar(diff);
  return diff;
}
#endif