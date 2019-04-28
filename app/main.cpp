#include "arboles.hpp"
#include "ioagen.hpp"
#include <fstream>
#include <iostream>

using namespace Enlazada;

int main() {
  std::ifstream isa("files/fig.txt", std::ifstream::binary);
  Agen<char> A;
  isa >> A;
  isa.close();
  std::cout << A << std::endl;
}
