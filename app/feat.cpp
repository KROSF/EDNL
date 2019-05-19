#include <iostream>
#include "grafos/io.hpp"
#include "practicas/P7.hpp"
using namespace grafos::pmc;
using std::vector;

std::ostream& operator<<(std::ostream& os, const alg::arista<short>& a) {
  os << "(" << a.orig << ", " << a.dest << ") = " << a.coste;
  return os;
}

int main(int argc, char** argv) {
  GrafoP<short> G(argv[1]);
  matriz<vertice<short>> P;
  matriz<short> F{alg::FloydMax(G, P)};
  arista<short> a{OtraVezUnGrafoSA(G)};
  std::cout << a << std::endl;
  std::cout << F << std::endl;
}