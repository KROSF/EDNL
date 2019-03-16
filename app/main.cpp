#include "abin_p2.hpp"
#include "ioabin.hpp"
#include "pathabin.hpp"
#include <fstream>
#include <iostream>

using namespace Enlazada;

int main() {
  Abin<char> OP;
  std::ifstream is("complete.txt",std::ifstream::binary);
  is >> OP;
  std::cout << OP << std::endl;
}
