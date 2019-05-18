#include <iostream>
#include <tuple>
#include "grafos/io.hpp"
#include "practicas/P6.hpp"
using namespace grafos::pmc;
using std::vector;
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T, T>& t) {
  os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ")";
  return os;
}

int main(void) {
  GrafoP<unsigned> G("files/grafos/conexo.txt");
  matriz<vertice<unsigned>> P;
  matriz<unsigned> F{Floyd(G, P)};
  size_t n{F.dimension()};
  vector<size_t> diam(n, 0);
  std::cout << F << std::endl;
  for (size_t i = 0; i < n; ++i) {
    const auto& [max_a, max_b] = TwoHighestValues<unsigned>(F[i]);
    if (std::get<0>(max_b) == GrafoP<unsigned>::INFINITO ||
        std::get<0>(max_a) == GrafoP<unsigned>::INFINITO) {
      diam[i] = GrafoP<unsigned>::INFINITO;
    } else {
      diam[i] = std::get<1>(max_a) + std::get<1>(max_b);
    }
    std::cout << i << " : " << max_a << " " << max_b << "  suma=" << diam[i]
              << std::endl;
  }
  std::cout << diam << std::endl;
  auto nodo = std::min_element(diam.begin(), diam.end());
  std::cout << *nodo << std::endl;
}