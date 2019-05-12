#ifndef GRAFOS_PLA_HPP
#define GRAFOS_PLA_HPP
#include <fstream>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include "grafos/lista.hpp"
using std::vector;
namespace grafos::pla {
template <typename T>
// Grafo ponderado PLA
class GrafoP {
 public:
  // Tipo de peso de las aristas.
  using tCoste = T;
  // Tipo que representa un vertice del grafo.
  using vertice = std::size_t;
  // Vertice Adyacente
  using tCamino = Lista<vertice>;
  // Limite maximo del tipo
  inline static const tCoste INFINITO = std::numeric_limits<T>::max();
  // Coste del vertice adyacente
  struct vertice_coste {
    vertice v;
    tCoste c;
    bool operator==(const vertice_coste& vc) const { return v == vc.v; }
  };
  // Crea un grafo ponderado PLA
  explicit GrafoP(std::size_t n) : ady(n) {}
  // Crea un grafo ponderado PLA desde fichero.
  explicit GrafoP(std::string_view path);
  // Numero de vertices del grafo.
  std::size_t numVert() const { return ady.size(); }
  // Lista de coste del vertice adyacente.
  const Lista<vertice_coste>& adyacentes(vertice v) const { return ady[v]; }
  // Lista de coste del vertice adyacente.
  Lista<vertice_coste>& adyacentes(vertice v) { return ady[v]; }

 private:
  vector<Lista<vertice_coste>> ady;
};

template <typename T>
GrafoP<T>::GrafoP(std::string_view path) {
  char c;
  std::string cad;
  vertice v;
  tCoste p;
  vertice_coste vc;
  std::ifstream file(path.data());
  unsigned n;

  file >> n;
  ady = vector<Lista<vertice_coste>>(n);
  while (file >> v) {
    file >> c;
    std::getline(file, cad);
    std::istringstream ss(cad);
    while (ss >> vc.v && ss >> vc.c) ady[v].insertar(vc, ady[v].fin());
  }
  file.close();
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const GrafoP<T>& g) {
  using vertice = typename GrafoP<T>::vertice;
  using posicion = typename Lista<typename GrafoP<T>::vertice_coste>::posicion;
  const size_t n = g.numVert();
  os << n << " vertices" << std::endl;
  for (vertice i = 0; i < n; i++)
    if (g.adyacentes(i).primera() != g.adyacentes(i).fin()) {
      os << i << ':';
      for (posicion p = g.adyacentes(i).primera(); p != g.adyacentes(i).fin();
           p = g.adyacentes(i).siguiente(p))
        os << ' ' << g.adyacentes(i).elemento(p).v << ' '
           << g.adyacentes(i).elemento(p).c;
      os << std::endl;
    }
  return os;
}

}  // namespace grafos::pla
#endif