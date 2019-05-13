#include <iostream>
#include "grafos/io.hpp"
#include "practicas/P6.hpp"

using namespace grafos;
using namespace pmc;
using std::cout;
using std::endl;
using std::vector;

int main(void) {
  GrafoP<int> G("files/grafos/dirigido3.txt");
  cout << std::boolalpha << esAciclico(G) << endl;
  matriz<alg::vertice<int>> P;
  matriz<int> F{alg::Floyd(G, P)};
  cout << G << endl;
  cout << P << endl;
  cout << F << endl;
}