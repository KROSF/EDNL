#include "ioagen.hpp"
#include "agen_p1.hpp"
#include <fstream>
#include <iostream>

using namespace Enlazada;

int main() {
  std::ifstream isa("files/agen_int.txt", std::ifstream::binary);
  Agen<int> A;
  isa >> A;
  isa.close();
  std::cout << A << std::endl;
  poda(A, 2);
  std::cout << A << std::endl;
}
