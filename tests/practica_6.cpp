#include <gtest/gtest.h>
#include "practicas/P6.hpp"
using namespace grafos::pmc;
using std::vector;
class DISABLED_Practica_6 : public ::testing::Test {
 protected:
  void SetUp() override {}
  vector<alg::vertice<unsigned>> P;
};

TEST_F(DISABLED_Practica_6, ejercicio_1_DijkstraInv) {
  GrafoP<unsigned> G("files/grafos/dijkstrainv.txt");
  vector<unsigned> Dinv = alg::DijkstraInv(G, 2, P);
}

TEST_F(DISABLED_Practica_6, ejercicio_2_pseudocentro) {
  GrafoP<unsigned> G("files/grafos/conexo.txt");
  PseudoCentro(G);
}

TEST_F(DISABLED_Practica_6, ejercicio_2_diametro) {
  GrafoP<unsigned> G("files/grafos/conexo.txt");
  Diametro(G);
}

TEST_F(DISABLED_Practica_6, ejercicio_3_Aciclico_true) {
  GrafoP<short> G("files/grafos/aciclico.txt");
  EXPECT_TRUE(esAciclico(G));
}

TEST_F(DISABLED_Practica_6, ejercicio_3_Aciclico_false) {
  GrafoP<unsigned> G("files/grafos/conexo.txt");
  EXPECT_FALSE(esAciclico(G));
}

TEST_F(DISABLED_Practica_6, ejercicio_4_Zuelandia) {
  GrafoP<unsigned> G("files/grafos/zuelandia.txt");
  vector<unsigned> ciudades{1, 2, 3, 4, 5, 6};
  vector<alg::arista<unsigned>> caminos{alg::arista<unsigned>(0, 0, 0)};
  matriz<unsigned> mcz = Zuelandia(G, ciudades, caminos, 3);
}

// TODO Ejercicio 5
