#include "abin.hpp"
#include <iostream>

using namespace Vectorial;

int main() {
  Abin<int> A(3);
  A.insertarRaiz(3);
  A.insertarHijoIzquierdo(A.raiz(), 2);
  A.insertarHijoDerecho(A.raiz(), 3);
  std::cout << A.elemento(A.raiz()) << std::endl;
}
