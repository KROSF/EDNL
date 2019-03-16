#include "abin_p2.hpp"
#include "ioabin.hpp"
#include "pathabin.hpp"
#include <fstream>
#include <iostream>

using namespace Enlazada;

int main() {
  // Abin<char> A;
  Abin<Op> B;
  // std::ifstream is("abin.txt", std::ifstream::binary);
  // is >> A;
  std::ifstream iss("/Users/krosf/Dev/uni/ednl/build/op.txt",
                    std::ifstream::binary);
  iss >> B;
  std::cout << operacion(B) << std::endl;
  std::cout << B << std::endl;
}
