#include "abin_p2.hpp"
#include "ioabin.hpp"
#include <fstream>
#include <iostream>

using namespace Enlazada;

// auto out = [](Abin<char> &a, const Abin<char>::Nodo &n) {
//   if (n != Abin<char>::NODO_NULO)
//     std::cout << a.elemento(n);
// };

int main() {
  Abin<char> A, B;
  std::ifstream is("abin.txt", std::ifstream::binary);
  is >> A;
  // B = A;
  // B.insertarHijoDrchoB(B.hijoDrchoB(B.hijoDrchoB(B.hijoDrchoB(B.raizB()))),
  //                      'm');
  B = reflejo(A);
  std::cout << A << std::endl;
  std::cout << B << std::endl;
}
