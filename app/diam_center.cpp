#include <iostream>
#include "grafos/io.hpp"
#include "practicas/P8.hpp"
using namespace grafos::pmc;
using grafos::ma::Grafo;
using std::vector;

int main(void) {
  Grafo MA("files/grafos/tombuctu.txt");
  std::cout << MA << std::endl;
  vector<Ciudad> ciudades{{2, 4}, {-1, 5}, {2, 3}, {-8, 3}, {0, 1}, {4, -4}};
  auto [islas, floyd] = Tombuctu(ciudades, MA);
  std::cout << floyd << std::endl;
  std::cout << Tombuctu2(ciudades, MA) << std::endl;
}