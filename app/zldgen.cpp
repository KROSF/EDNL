#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include "grafos/io.hpp"
#include "practicas/P7.hpp"
using namespace grafos::pmc;
using grafos::pmc::GrafoP;
using grafos::pmc::alg::vertice;
void file(std::string seed, std::string name) {
  std::random_device generator;
  std::uniform_int_distribution<int> rand(1, 100);
  GrafoP<int> G(seed);
  int sum = 0;
  for (vertice<int> v = 0; v < G.numVert(); ++v) {
    for (vertice<int> w = v + 1; w < G.numVert(); ++w) {
      if (G[v][w] != GrafoP<int>::INFINITO) {
        G[v][w] = G[w][v] = rand(generator);
      }
      ++sum;
    }
  }
  std::ofstream outfile(name);
  outfile << G.numVert() << '\n';
  for (vertice<int> v = 0; v < G.numVert(); ++v) {
    for (vertice<int> w = 0; w < G.numVert() - 1; ++w) {
      outfile << G[v][w] << " ";
    }
    outfile << G[v][G.numVert() - 1] << '\n';
  }
  outfile.close();
  std::cout << G << std::endl;
  std::cout << sum << std::endl;
}
int main(int argc, char** argv) {
  if (argc == 3) {
    file(argv[1], argv[2]);
  } else {
    std::cout << "El numero de parametros es incorrecto\n";
  }
}