#include <iostream>
#include <string>
#include "grafos/alg.hpp"
#include "grafos/io.hpp"

using namespace grafos;
using std::cout;
using std::endl;

int main(void) {
  std::string path("files/grafopmc.txt");
  pmc::GrafoP<int> G(path);
  cout << G << endl;
}