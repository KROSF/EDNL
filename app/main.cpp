#include "abin_p1.hpp"
#include "ioabin.hpp"
#include <fstream>
#include <iostream>

using namespace Enlazada;

auto out = [](Abin<char> &a, const Abin<char>::Nodo &n) {
  std::cout << a.elemento(n);
};
int main() {
  Abin<char> A;
  std::ifstream is("/Users/krosf/Dev/uni/ednl/build/abin.txt",
                   std::ifstream::binary);
  is >> A;
  inOrder<char>(A, out);
  std::cout << std::endl;
  postOrder<char>(A, out);
  std::cout << std::endl;
  preOrder<char>(A, out);
  std::cout << std::endl << A << std::endl;
}
