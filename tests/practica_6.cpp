#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "practicas/P6.hpp"
using namespace grafos::pmc;
using std::vector;
using ::testing::ElementsAre;
using ::testing::ElementsAreArray;
class Practica_6 : public ::testing::Test {
 protected:
  void SetUp() override {}
  vector<alg::vertice<unsigned>> P;
};

TEST_F(Practica_6, ejercicio_1_Dijkstra) {
  GrafoP<unsigned> G("files/grafos/dijkstrainv.txt");
  vector<unsigned> D = alg::Dijkstra(G, 2, P);
  ASSERT_THAT(D, ElementsAre(7, 5, 0, 7, 2, 3, 1, 8));
  ASSERT_THAT(P, ElementsAre(1, 2, 2, 1, 2, 6, 2, 4));
}

TEST_F(Practica_6, ejercicio_1_DijkstraInv) {
  GrafoP<unsigned> G("files/grafos/dijkstrainv.txt");
  vector<unsigned> Dinv = alg::DijkstraInv(G, 2, P);
  ASSERT_THAT(Dinv, ElementsAre(7, 5, 0, 7, 2, 3, 1, 8));
  ASSERT_THAT(P, ElementsAre(1, 2, 2, 1, 2, 6, 2, 4));
}

TEST_F(Practica_6, ejercicio_2_pseudocentro) {
  GrafoP<unsigned> G("files/grafos/conexo.txt");
  EXPECT_EQ(6U, PseudoCentro(G));
}

TEST_F(Practica_6, ejercicio_2_diametro) {
  GrafoP<unsigned> G("files/grafos/conexo.txt");
  EXPECT_EQ(12U, Diametro(G));
}

TEST_F(Practica_6, ejercicio_3_Aciclico_true) {
  GrafoP<short> G("files/grafos/aciclico.txt");
  EXPECT_TRUE(esAciclico(G));
}

TEST_F(Practica_6, ejercicio_3_Aciclico_false) {
  GrafoP<unsigned> G("files/grafos/conexo.txt");
  EXPECT_FALSE(esAciclico(G));
}

TEST_F(Practica_6, ejercicio_4_Zuelandia) {
  GrafoP<short> G("files/grafos/zuelandia.txt");
  vector<short> ciudades{2, 7, 11};
  short inf{GrafoP<short>::INFINITO};
  vector<alg::arista<short>> caminos{alg::arista<short>(8, 3),
                                     alg::arista<short>(12, 5)};
  matriz<short> mcz = Zuelandia(G, ciudades, caminos, 0);
  // clang-format off
  ASSERT_THAT(
    static_cast<vector<vector<short>>>(mcz),
    ElementsAreArray({
      ElementsAreArray<short>({  0,  18, inf,  20,   1,   3,   9, inf, inf,  13,  26, inf, inf}),
      ElementsAreArray<short>({ 34,   0, inf,  54,  35,  37,  43, inf, inf,  47,  60, inf, inf}),
      ElementsAreArray<short>({ 35,  53, inf,  55,  36,  38,  44, inf, inf,  48,  61, inf, inf}),
      ElementsAreArray<short>({ 32,  50, inf,   0,  33,  35,  41, inf, inf,  45,  58, inf, inf}),
      ElementsAreArray<short>({ 28,  46, inf,  48,   0,  31,  37, inf, inf,  41,  54, inf, inf}),
      ElementsAreArray<short>({ 26,  44, inf,  46,  27,   0,  35, inf, inf,  39,  52, inf, inf}),
      ElementsAreArray<short>({inf, inf, inf, inf, inf, inf,   0, inf, inf, inf, inf, inf, inf}),
      ElementsAreArray<short>({ 44,  62, inf,  64,  45,  47,  53, inf, inf,  57,  70, inf, inf}),
      ElementsAreArray<short>({ 28,  46, inf,  48,  29,  31,  37, inf,   0,  41,  54, inf, inf}),
      ElementsAreArray<short>({ 16,  34, inf,  36,  17,  19,  25, inf, inf,   0,  42, inf, inf}),
      ElementsAreArray<short>({  3,  21, inf,  23,   4,   6,  12, inf, inf,  16,   0, inf, inf}),
      ElementsAreArray<short>({ 48,  66, inf,  68,  49,  51,  57, inf, inf,  61,  74, inf, inf}),
      ElementsAreArray<short>({ 40,  58, inf,  60,  41,  43,  49, inf, inf,  53,  66, inf,   0})
    })
  );
  // clang-format on
}

// TODO Ejercicio 5
