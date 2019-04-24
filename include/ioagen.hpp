#include "agen.hpp"
#include "trunk.hpp"
#include <fstream>
#include <ostream>
#include <string>

namespace Enlazada {
template <typename T> using Nodo = typename Agen<T>::Nodo;

template <typename T>
void printAbin(std::ostream &os, const Agen<T> &a, const Nodo<T> &n,
               Trunk *prev, bool isLeft) {
  if (n == Agen<T>::NODO_NULO) {
    return;
  }
  std::string prev_str = "    ";
  Trunk *trunk = new Trunk(prev, prev_str);
  auto hijo = a.hijoIzqdo(n);
  if (hijo != Agen<T>::NODO_NULO) {
    printAbin(os, a, hijo, trunk, true);
    if (!prev) {
      trunk->_str = "    ";
    } else if (isLeft) {
      trunk->_str = "┌── ";
      prev_str = "    │";
    } else {
      trunk->_str = "└── ";
      prev->_str = prev_str;
    }
    showTrunks(os, trunk);
    os << a.elemento(n) << std::endl;
    while ((hijo = a.hermDrcho(hijo)) != Agen<T>::NODO_NULO) {
      printAbin(os, a, hijo, trunk, false);
    }
  } else {
    if (!prev) {
      trunk->_str = "    ";
    } else if (isLeft) {
      trunk->_str = "┌── ";
      prev_str = "    │";
    } else {
      trunk->_str = "└── ";
      prev->_str = prev_str;
    }
    showTrunks(os, trunk);
    os << a.elemento(n) << std::endl;
  }
}

template <typename T>
void readAgen(std::ifstream &ifs, Agen<T> &a, const Nodo<T> &n, const T &fin) {
  T ehi, ehd;
  if (ifs >> ehi && ehi != fin) {
    a.insertarHijoIzqdo(n, ehi);
    readAgen(ifs, a, a.hijoIzqdo(n), fin);
    auto hijo = a.hijoIzqdo(n);
    while (ifs >> ehd && ehd != fin) {
      a.insertarHermDrcho(hijo, ehd);
      readAgen(ifs, a, a.hermDrcho(hijo), fin);
      hijo = a.hermDrcho(hijo);
    }
  }
}

template <typename T>
std::ifstream &operator>>(std::ifstream &ifs, Agen<T> &a) {
  T e, fin;
  if (a.arbolVacio() && ifs >> fin && ifs >> e && e != fin) {
    a.insertarRaiz(e);
    readAgen(ifs, a, a.raiz(), fin);
  }
  return ifs;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Agen<T> &a) {
  printAbin(os, a, a.raiz(), nullptr, false);
  return os;
}

} // namespace Enlazada