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
  GrafoP<short> G("files/grafos/aciclico.txt");
  matriz<vertice<short>> P;
  matriz<short> F{Floyd(G, P)};
  size_t n{F.dimension()};
  vector<size_t> diam(n, 0);
  std::cout << F << std::endl;
  for (size_t i = 0; i < n; ++i) {
    const auto& [max_a, max_b] = TwoHighestValues<short>(F[i]);
    if (std::get<0>(max_b) == GrafoP<short>::INFINITO ||
        std::get<0>(max_a) == GrafoP<short>::INFINITO) {
      diam[i] = GrafoP<short>::INFINITO;
    } else {
      diam[i] = std::get<1>(max_a) + std::get<1>(max_b);
    }
    std::cout << i << " : " << max_a << " " << max_b << "  suma=" << diam[i]
              << std::endl;
  }
  std::cout << diam << std::endl;
  auto nodo = std::min_element(diam.begin(), diam.end());
  std::cout << *nodo << std::endl;
  std::cout << std::distance(diam.begin(), nodo) << std::endl;
}