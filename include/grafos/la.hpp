#ifndef GRAFOS_LA_HPP
#define GRAFOS_LA_HPP
#include <fstream>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include "grafos/lista.hpp"

namespace grafos::la {
// Grafo no ponderado LA
class Grafo {
 public:
  // Tipo que representa los vertices del grafo.
  using vertice = std::size_t;
  // Crea un Grafo no ponderado.
  explicit Grafo(std::size_t n) : ady(n) {}
  // Crea un Grafo no ponderado desde un fichero.
  explicit Grafo(std::string_view path);
  // Devuelve el numero de vertices del grafo.
  std::size_t numVert() const { return ady.size(); }
  // Devuelve un lista de los vertices adyacentes.
  const Lista<vertice>& adyacentes(vertice v) const { return ady[v]; }
  // Modificador de la lista de los vertices adyacentes.
  Lista<vertice>& adyacentes(vertice v) { return ady[v]; }

 private:
  // Vector de la lista de vertices adyaventes
  std::vector<Lista<vertice>> ady;
};

Grafo::Grafo(std::string_view path) {
  char c;
  std::string cad;
  vertice v, w;
  std::ifstream file(path.data());
  unsigned n;
  file >> n;
  ady = std::vector<Lista<vertice>>(n);
  while (file >> v) {
    file >> c;
    std::getline(file, cad);
    std::istringstream ss(cad);
    while (ss >> w) ady[v].insertar(w, ady[v].fin());
  }
  file.close();
}

std::ostream& operator<<(std::ostream& os, const Grafo& g) {
  using vertice = Grafo::vertice;
  using posicion = typename Lista<vertice>::posicion;
  const std::size_t n = g.numVert();
  os << n << " vertices" << std::endl;
  for (vertice i = 0; i < n; ++i)
    if (g.adyacentes(i).primera() != g.adyacentes(i).fin()) {
      os << i << ':';
      for (posicion p = g.adyacentes(i).primera(); p != g.adyacentes(i).fin();
           p = g.adyacentes(i).siguiente(p))
        os << ' ' << g.adyacentes(i).elemento(p);
      os << std::endl;
    }
  return os;
}

}  // namespace grafos::la
#endif