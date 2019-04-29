#ifndef MATRIZ_HPP
#define MATRIZ_HPP
#include <vector>
namespace grafos {
template <typename T>
class matriz {
 public:
  matriz() {}
  explicit matriz(size_t n, const T& x = T()) : m(n, std::vector<T>(n, x)) {}
  size_t dimension() const { return m.size(); }
  const std::vector<T>& operator[](size_t i) const { return m[i]; }
  std::vector<T>& operator[](size_t i) { return m[i]; }

 private:
  std::vector<std::vector<T> > m;
};
}  // namespace grafos
#endif