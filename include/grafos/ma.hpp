#ifndef GRAFO_MA_HPP
#define GRAFO_MA_HPP
#include <fstream>
#include <iomanip>
#include <ostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
using std::vector;
namespace grafos {
namespace pmc {
template <typename T>
class GrafoP;
}
namespace ma {
// Grafo no ponderado MA
class Grafo {
 public:
  // Tipo que representa los vertices del grafo.
  using vertice = std::size_t;
  // Crea un Grafo no ponderado MA
  explicit Grafo(std::size_t n) : ady(n, vector<bool>(n, false)) {}
  // Crea un grafo desde un fichero
  explicit Grafo(std::string_view path);
  template <typename T>
  // Copia un grado ponderado a grafo MA
  explicit Grafo(const pmc::GrafoP<T>& G)
      : ady(G.numVert(), vector<bool>(G.numVert())) {
    const size_t n = G.numVert();
    for (vertice i = 0; i < n; ++i)
      for (vertice j = 0; j < n; ++j)
        ady[i][j] = (G[i][j] != pmc::GrafoP<T>::INFINITO);
  }
  // Numero de vertices del grafo.
  std::size_t numVert() const { return ady.size(); }
  const vector<bool>& operator[](vertice v) const { return ady[v]; }
  vector<bool>& operator[](vertice v) { return ady[v]; }
  // Comprueba si el grafo es dirigido.
  bool esDirigido() const;

 private:
  // matrix de adyacencia.
  vector<vector<bool>> ady;
};

Grafo::Grafo(std::string_view path) {
  char c;
  std::string cad;
  vertice v, w;
  std::ifstream file(path.data());
  unsigned n;

  file >> n;
  ady = vector<vector<bool>>(n, vector<bool>(n, false));
  while (file >> v) {
    file >> c;
    std::getline(file, cad);
    std::istringstream ss(cad);
    while (ss >> w) ady[v][w] = true;
  }
  file.close();
}

bool Grafo::esDirigido() const {
  bool s = true;
  const std::size_t n = numVert();
  vertice i = 0;
  while (s && i < n) {
    vertice j = i + 1;
    while (s && j < n) {
      s = (ady[i][j] == ady[j][i]);
      ++j;
    }
    ++i;
  }
  return !s;
}

std::ostream& operator<<(std::ostream& os, const Grafo& g) {
  using vertice = Grafo::vertice;
  const std::size_t n = g.numVert();
  os << n << " vertices" << std::endl;
  os << "   ";
  for (vertice j = 0; j < n; ++j) os << std::setw(3) << j;
  os << std::endl;
  for (vertice i = 0; i < n; ++i) {
    os << std::setw(3) << i;
    for (vertice j = 0; j < n; ++j) os << std::setw(3) << g[i][j];
    os << std::endl;
  }
  return os;
}

}  // namespace ma
}  // namespace grafos

#endif