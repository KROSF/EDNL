#ifndef MATRIZ_HPP
#define MATRIZ_HPP
#include <vector>
namespace grafos {
template <typename T>
// Matriz Generica
class matriz {
 public:
  // Crea una matriz vacia
  matriz() {}
  // Crea un matriz de n x n rellena de x
  explicit matriz(size_t n, const T& x = T()) : m(n, std::vector<T>(n, x)) {}
  // Devuelve la dimension de la matriz.
  std::size_t dimension() const { return m.size(); }
  operator std::vector<std::vector<T>>() { return m; }
  const std::vector<T>& operator[](size_t i) const { return m[i]; }
  std::vector<T>& operator[](size_t i) { return m[i]; }

 private:
  // Matriz
  std::vector<std::vector<T>> m;
};
}  // namespace grafos
#endif