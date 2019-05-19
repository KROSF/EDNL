#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "practicas/P6.hpp"
#include "practicas/P7.hpp"

using namespace grafos::pmc;
using alg::arista;
using grafos::Lista;
using std::vector;
using ::testing::ElementsAre;
using ::testing::ElementsAreArray;
class Practica_6 : public ::testing::Test {
 protected:
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
  vector<arista<short>> caminos{arista<short>(8, 3), arista<short>(12, 5)};
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

class Practica_7 : public ::testing::Test {};

TEST_F(Practica_7, ejercicio_1_otravezungrafo) {
  GrafoP<short> G("files/grafos/aciclico.txt");
  ASSERT_EQ(arista<short>(0, 10, 80), OtraVezUnGrafoSA(G));
}

TEST_F(Practica_7, ejercicio_2_laberinto) {
  std::vector<arista<int>> m{
      arista<int>(0, 1),   arista<int>(2, 3),   arista<int>(6, 7),
      arista<int>(8, 9),   arista<int>(7, 12),  arista<int>(8, 13),
      arista<int>(10, 11), arista<int>(13, 14), arista<int>(11, 16),
      arista<int>(12, 17), arista<int>(18, 19), arista<int>(15, 16),
      arista<int>(20, 21), arista<int>(17, 22), arista<int>(18, 23),
      arista<int>(22, 23)};
  Lista<arista<int>> muros;
  for (auto e : m) {
    muros.insertar(e, muros.fin());
  }
  std::vector<int> expect;
  auto [coste, camino] = Laberinto<int>(5, muros, 2, 22);
  for (auto it = camino.primera(); it != camino.fin();
       it = camino.siguiente(it)) {
    expect.push_back(camino.elemento(it));
  }
  ASSERT_EQ(10, coste);
  ASSERT_THAT(expect,
              ElementsAreArray({2, 1, 6, 11, 12, 13, 18, 17, 16, 21, 22}));
}