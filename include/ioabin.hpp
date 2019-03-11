#ifndef IOABIN_HPP
#define IOABIN_HPP
#include "abin.hpp"
#include "trunk.hpp"
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

namespace Vectorial {
template <typename T> using Nodo = typename Abin<T>::Nodo;
template <typename T>
using Callback = std::function<void(Abin<T> &, const Nodo<T> &)>;

template <typename T>
void printAbin(std::ostream &os, const Abin<T> &a, const Nodo<T> &n,
               Trunk *prev, bool isLeft) {
  if (n == Abin<T>::NODO_NULO) {
    return;
  }
  std::string prev_str = "    ";
  Trunk *trunk = new Trunk(prev, prev_str);
  printAbin(os, a, a.hijoDrchoB(n), trunk, true);
  if (!prev) {
    trunk->_str = "---";
  } else if (isLeft) {
    trunk->_str = ".---";
    prev_str = "    |";
  } else {
    trunk->_str = "`---";
    prev->_str = prev_str;
  }
  showTrunks(os, trunk);
  os << "(" << a.elemento(n) << ")" << std::endl;
  if (prev) {
    prev->_str = prev_str;
  }
  trunk->_str = "    |";
  printAbin(os, a, a.hijoIzqdoB(n), trunk, false);
}

template <typename T>
void readAbin(std::ifstream &ifs, Abin<T> &a, const Nodo<T> &n, const T &fin) {
  T elto_izq, elto_dch;
  if (ifs >> elto_izq && elto_izq != fin) {
    a.insertarHijoIzqdoB(n, elto_izq);
    readAbin(ifs, a, a.hijoIzqdoB(n), fin);
  }
  if (ifs >> elto_dch && elto_dch != fin) {
    a.insertarHijoDrchoB(n, elto_dch);
    readAbin(ifs, a, a.hijoDrchoB(n), fin);
  }
}

template <typename T>
std::ifstream &operator>>(std::ifstream &ifs, Abin<T> &a) {
  T elto, fin;
  if (a.arbolVacioB() && ifs >> fin && ifs >> elto && elto != fin) {
    a.insertarRaizB(elto);
    readAbin(ifs, a, a.raizB(), fin);
  }
  return ifs;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const Abin<T> &a) {
  printAbin(os, a, a.raizB(), nullptr, false);
  return os;
}

template <typename T>
void preOrder_r(Abin<T> &a, const Nodo<T> n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    procesar(a, n);
    preOrder_r(a, a.hijoIzqdoB(n), procesar);
    preOrder_r(a, a.hijoDrchoB(n), procesar);
  }
}

template <typename T> void preOrder(Abin<T> &a, Callback<T> procesar) {
  preOrder_r(a, a.raizB(), procesar);
}

template <typename T>
void inOrder_r(Abin<T> &a, const Nodo<T> &n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    inOrder_r(a, a.hijoIzqdoB(n), procesar);
    procesar(a, n);
    inOrder_r(a, a.hijoDrchoB(n), procesar);
  }
}

template <typename T> void inOrder(Abin<T> &a, Callback<T> procesar) {
  inOrder_r(a, a.raizB(), procesar);
}

template <typename T>
void postOrder_r(Abin<T> &a, const Nodo<T> &n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    postOrder_r(a, a.hijoIzqdoB(n), procesar);
    postOrder_r(a, a.hijoDrchoB(n), procesar);
    procesar(a, n);
  }
}

template <typename T> void postOrder(Abin<T> &a, Callback<T> procesar) {
  postOrder_r(a, a.raizB(), procesar);
}

} // namespace Vectorial

namespace Enlazada {
template <typename T> using Nodo = typename Abin<T>::Nodo;
template <typename T>
using Callback = std::function<void(Abin<T> &, const Nodo<T> &)>;

template <typename T>
void printAbin(std::ostream &os, const Abin<T> &a, const Nodo<T> &n,
               Trunk *prev, bool isLeft) {
  if (n == Abin<T>::NODO_NULO) {
    return;
  }
  std::string prev_str = "    ";
  Trunk *trunk = new Trunk(prev, prev_str);
  printAbin(os, a, a.hijoDrchoB(n), trunk, true);
  if (!prev) {
    trunk->_str = "--- ";
  } else if (isLeft) {
    trunk->_str = ".--- ";
    prev_str = "    |";
  } else {
    trunk->_str = "`--- ";
    prev->_str = prev_str;
  }
  showTrunks(os, trunk);
  os << a.elemento(n) << std::endl;
  if (prev) {
    prev->_str = prev_str;
  }
  trunk->_str = "    |";
  printAbin(os, a, a.hijoIzqdoB(n), trunk, false);
}

template <typename T>
void readAbin(std::ifstream &ifs, Abin<T> &a, const Nodo<T> &n, const T &fin) {
  T elto_izq, elto_dch;
  if (ifs >> elto_izq && elto_izq != fin) {
    a.insertarHijoIzqdoB(n, elto_izq);
    readAbin(ifs, a, a.hijoIzqdoB(n), fin);
  }
  if (ifs >> elto_dch && elto_dch != fin) {
    a.insertarHijoDrchoB(n, elto_dch);
    readAbin(ifs, a, a.hijoDrchoB(n), fin);
  }
}

template <typename T>
std::ifstream &operator>>(std::ifstream &ifs, Abin<T> &a) {
  T elto, fin;
  if (a.arbolVacioB() && ifs >> fin && ifs >> elto && elto != fin) {
    a.insertarRaizB(elto);
    readAbin(ifs, a, a.raizB(), fin);
  }
  return ifs;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const Abin<T> &a) {
  printAbin(os, a, a.raizB(), nullptr, false);
  return os;
}

template <typename T>
void preOrder_r(Abin<T> &a, const Nodo<T> n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    procesar(a, n);
    preOrder_r(a, a.hijoIzqdoB(n), procesar);
    preOrder_r(a, a.hijoDrchoB(n), procesar);
  }
}

template <typename T> void preOrder(Abin<T> &a, Callback<T> procesar) {
  preOrder_r(a, a.raizB(), procesar);
}

template <typename T>
void inOrder_r(Abin<T> &a, const Nodo<T> &n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    inOrder_r(a, a.hijoIzqdoB(n), procesar);
    procesar(a, n);
    inOrder_r(a, a.hijoDrchoB(n), procesar);
  }
}

template <typename T> void inOrder(Abin<T> &a, Callback<T> procesar) {
  inOrder_r(a, a.raizB(), procesar);
}

template <typename T>
void postOrder_r(Abin<T> &a, const Nodo<T> &n, Callback<T> procesar) {
  if (n != Abin<T>::NODO_NULO) {
    postOrder_r(a, a.hijoIzqdoB(n), procesar);
    postOrder_r(a, a.hijoDrchoB(n), procesar);
    procesar(a, n);
  }
}

template <typename T> void postOrder(Abin<T> &a, Callback<T> procesar) {
  postOrder_r(a, a.raizB(), procesar);
}

} // namespace Enlazada
#endif
