#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include "grafos/alg.hpp"
#include "grafos/io.hpp"

using grafos::pmc::GrafoP;
using grafos::pmc::alg::vertice;

int main(void) {
  std::random_device generator;
  std::uniform_int_distribution<short> rand(1, 100);
  GrafoP<short> G("files/grafos/zuelandia.txt");
  std::cout << G << std::endl;
  for (vertice<short> v = 0; v < G.numVert(); ++v) {
    for (vertice<short> w = 0; w < G.numVert(); ++w) {
      if (G[v][w] != GrafoP<short>::INFINITO) {
        G[v][w] = rand(generator);
      }
    }
  }
  std::ofstream outfile("zl.txt");
  outfile << G.numVert() << '\n';
  for (vertice<short> v = 0; v < G.numVert(); ++v) {
    for (vertice<short> w = 0; w < G.numVert() - 1; ++w) {
      outfile << G[v][w] << " ";
    }
    outfile << G[v][G.numVert() - 1] << '\n';
  }
  outfile.close();
}