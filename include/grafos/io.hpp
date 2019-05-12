#ifndef GRAFOS_IO_HPP
#define GRAFOS_IO_HPP
#include <ostream>
#include <vector>
#include "grafos/lista.hpp"
#include "grafos/matriz.hpp"
#include "grafos/pmc.hpp"

namespace grafos {
namespace pmc {
template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v) {
  for (size_t i = 0; i < v.size(); i++) {
    os << std::setw(4);
    if (v[i] != GrafoP<T>::INFINITO)
      os << v[i];
    else
      os << "-";
  }
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const matriz<T>& m) {
  const size_t n = m.dimension();
  os << "    ";
  for (size_t j = 0; j < n; ++j) os << std::setw(4) << j;
  os << std::endl;
  for (size_t i = 0; i < n; ++i) {
    os << std::setw(4) << i;
    for (size_t j = 0; j < n; ++j) {
      os << std::setw(4);
      if (m[i][j] == GrafoP<T>::INFINITO)
        os << "-";
      else
        os << m[i][j];
    }
    os << std::endl;
  }
  return os;
}
}  // namespace pmc
namespace pla {
template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v) {
  for (size_t i = 0; i < v.size(); i++) {
    os << std::setw(4);
    if (v[i] != GrafoP<T>::INFINITO)
      os << v[i];
    else
      os << "-";
  }
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const matriz<T>& m) {
  const size_t n = m.dimension();
  os << "    ";
  for (size_t j = 0; j < n; ++j) os << std::setw(4) << j;
  os << std::endl;
  for (size_t i = 0; i < n; ++i) {
    os << std::setw(4) << i;
    for (size_t j = 0; j < n; ++j) {
      os << std::setw(4);
      if (m[i][j] == GrafoP<T>::INFINITO)
        os << "-";
      else
        os << m[i][j];
    }
    os << std::endl;
  }
  return os;
}
}  // namespace pla

std::ostream& operator<<(std::ostream& os, const matriz<bool>& m) {
  const size_t n = m.dimension();
  os << "   ";
  for (size_t j = 0; j < n; ++j) os << std::setw(3) << j;
  os << std::endl;
  for (size_t i = 0; i < n; ++i) {
    os << std::setw(3) << i;
    for (size_t j = 0; j < n; ++j) os << std::setw(3) << m[i][j];
    os << std::endl;
  }
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream&, const Lista<T>&);

std::ostream& operator<<(std::ostream& os, const Lista<std::size_t>& L) {
  using posicion = Lista<std::size_t>::posicion;
  for (posicion i = L.primera(); i != L.fin(); i = L.siguiente(i))
    os << L.elemento(i) << ' ';
  return os;
}
}  // namespace grafos
#endif