#ifndef PATHABIN_HPP
#define PATHABIN_HPP

#include "abin.hpp"
#include <stack>

namespace Vectorial {

template <typename T> using Nodo = typename Abin<T>::Nodo;

template <typename T>
using Callback = std::function<void(Abin<T> &, const Nodo<T> &)>;

template <typename T>
void preOrder(Abin<T> &a, const Nodo<T> n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    procesar(a, n);
    preOrder(a, a.hijoIzqdoB(n), procesar);
    preOrder(a, a.hijoDrchoB(n), procesar);
  }
}

template <typename T>
void inOrder(Abin<T> &a, const Nodo<T> &n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    inOrder(a, a.hijoIzqdoB(n), procesar);
    procesar(a, n);
    inOrder(a, a.hijoDrchoB(n), procesar);
  }
}

template <typename T>
void postOrder(Abin<T> &a, const Nodo<T> &n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    postOrder(a, a.hijoIzqdoB(n), procesar);
    postOrder(a, a.hijoDrchoB(n), procesar);
    procesar(a, n);
  }
}

#ifdef ITER
template <typename T>
void preOrderIter(Abin<T> &a, Nodo<T> n, Callback<T> procesar) {}

template <typename T>
void inOrderIter(Abin<T> &a, Nodo<T> n, Callback<T> procesar) {}

template <typename T>
void postOrderIter(Abin<T> &a, Nodo<T> n, Callback<T> procesar) {}
#endif

} // namespace Vectorial

namespace Enlazada {

template <typename T> using Nodo = typename Abin<T>::Nodo;

template <typename T>
using Callback = std::function<void(Abin<T> &, const Nodo<T> &)>;

template <typename T>
void preOrder(Abin<T> &a, const Nodo<T> n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    procesar(a, n);
    preOrder(a, a.hijoIzqdoB(n), procesar);
    preOrder(a, a.hijoDrchoB(n), procesar);
  }
}

template <typename T>
void inOrder(Abin<T> &a, const Nodo<T> &n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    inOrder(a, a.hijoIzqdoB(n), procesar);
    procesar(a, n);
    inOrder(a, a.hijoDrchoB(n), procesar);
  }
}

template <typename T>
void postOrder(Abin<T> &a, const Nodo<T> &n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    postOrder(a, a.hijoIzqdoB(n), procesar);
    postOrder(a, a.hijoDrchoB(n), procesar);
    procesar(a, n);
  }
}

#ifdef ITER
template <typename T>
void preOrderIter(Abin<T> &a, Nodo<T> n, Callback<T> procesar) {
  std::stack<Nodo<T>> pila;
  do {
    if (n != Abin<T>::NODO_NULO) {
      procesar(a, n);
      if (a.hijoDrchoB(n) != Abin<T>::NODO_NULO) {
        pila.push(a.hijoDrchoB(n));
      }
      n = a.hijoIzqdoB(n);
    } else if (!pila.empty()) {
      n = pila.top();
      pila.pop();
    }
  } while (!(n == Abin<T>::NODO_NULO && pila.empty()));
}

template <typename T>
void inOrderIter(Abin<T> &a, Nodo<T> n, Callback<T> procesar) {}

template <typename T>
void postOrderIter(Abin<T> &a, Nodo<T> n, Callback<T> procesar) {}
#endif

} // namespace Enlazada
#endif