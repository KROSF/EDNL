#include <iostream>
#include "grafos/io.hpp"
#include "practicas/P8.hpp"
using namespace grafos::pmc;
using grafos::ma::Grafo;
using std::vector;

int main(void) {
  Grafo MA("files/grafos/tombuctu.txt");
  vector<Ciudad> ciudades{{2, 4},  {-1, 5}, {2, 3},  {-8, 3}, {0, 1},
                          {4, -4}, {6, 8},  {4, 10}, {10, 11}};
  auto camino = Tombuctu2(ciudades, MA);
  for (auto & a : camino) {
    std::cout << a.orig << " " << a.dest << " " << a.coste << std::endl;
  }
}