#include "agen_p1.hpp"
#include "ioagen.hpp"
#include <fstream>
#include <iostream>

using namespace Enlazada;

int main() {
  Agen<char> OP;
  std::ifstream is("files/agen_out.txt", std::ifstream::binary);
  is >> OP;
  std::cout << OP << std::endl;
}
