#include "abin_p2.hpp"
#include "ioabin.hpp"
#include "pathabin.hpp"
#include <fstream>
#include <iostream>

using namespace Enlazada;

int main() {
  Abin<char> A;
  std::ifstream is("pseudocmp.txt", std::ifstream::binary);
  is >> A;
  Abin<char> B{reflejo(A)};
  std::string reflejado;
  preOrder<char>(B, B.raizB(), [&reflejado](Abin<char> &a, const Nodo<char> &n) {
    std::cout << a.elemento(n);
    reflejado += a.elemento(n);
  });
  std::cout <<std::endl<< reflejado << std::endl;
  std::cout << std::endl;
  preOrder<char>(A, A.raizB(), [](Abin<char> &a, const Nodo<char> &n) {
    std::cout << a.elemento(n);
  });
}
