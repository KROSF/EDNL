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
  const std::size_t n = m.dimension();
  std::size_t digits{0};
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = 0; j < n; ++j) {
      if (m[i][j] != GrafoP<T>::INFINITO &&
          static_cast<std::size_t>(m[i][j]) > digits) {
        digits = m[i][j];
      }
    }
  }
  digits = std::to_string(digits).size() + 1;
  os << "\033[1m\033[32m ";
  for (std::size_t j = 0; j < n; ++j) {
    os << std::setw(digits) << j;
  }
  os << "\033[00m\n";
  for (std::size_t i = 0; i < n; ++i) {
    os << "\033[1m\033[32m" << i << "\033[00m" << std::setw(digits);
    for (std::size_t j = 0; j < n; ++j) {
      if (m[i][j] == GrafoP<T>::INFINITO) {
        os << std::setw(digits + 16) << "\033[1m\033[34m\u221E\033[00m";
      } else {
        os << std::setw(digits) << m[i][j];
      }
    }
    os << std::endl;
  }
  return os;
}
}  // namespace pmc

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