#include <iostream>
#include "grafos/io.hpp"
#include "practicas/P6.hpp"
using namespace grafos::pmc;
using std::vector;
int main(int argc, char **argv) {
  GrafoP<unsigned> G(argv[1]);
  matriz<vertice<unsigned>> P;
  matriz<unsigned> F{alg::Floyd(G, P)};
  std::cout << G << std::endl;
  std::cout << F << std::endl;
}