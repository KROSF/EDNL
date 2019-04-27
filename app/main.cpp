#include "abb.hpp"
#include "abb_px.hpp"
#include "ioabin.hpp"
#include <fstream>
#include <iostream>

using namespace Enlazada;

int main() {
  std::ifstream isa("files/abb_poda.txt", std::ifstream::binary);
  Abin<int> A;
  isa >> A;
  isa.close();
  std::cout << A << std::endl;
  Abb<int> a{A};
  a.podar(9);
  std::cout << static_cast<Abin<int>>(a) << std::endl;
}
