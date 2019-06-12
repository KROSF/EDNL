#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "practicas/P6.hpp"
#include "practicas/P7.hpp"

using namespace grafos::pmc;
using alg::arista;
using alg::BigGrafo;
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
    ElementsAreArray<vector<short>>({
      {  0,  18, inf,  20,   1,   3,   9, inf, inf,  13,  26, inf, inf},
      { 34,   0, inf,  54,  35,  37,  43, inf, inf,  47,  60, inf, inf},
      { 35,  53, inf,  55,  36,  38,  44, inf, inf,  48,  61, inf, inf},
      { 32,  50, inf,   0,  33,  35,  41, inf, inf,  45,  58, inf, inf},
      { 28,  46, inf,  48,   0,  31,  37, inf, inf,  41,  54, inf, inf},
      { 26,  44, inf,  46,  27,   0,  35, inf, inf,  39,  52, inf, inf},
      {inf, inf, inf, inf, inf, inf,   0, inf, inf, inf, inf, inf, inf},
      {  1,  19, inf,  21,   2,   4,  10, inf, inf,  14,  27, inf, inf},
      { 28,  46, inf,  48,  29,  31,  37, inf,   0,  41,  54, inf, inf},
      { 16,  34, inf,  36,  17,  19,  25, inf, inf,   0,  42, inf, inf},
      {  3,  21, inf,  23,   4,   6,  12, inf, inf,  16,   0, inf, inf},
      { 48,  66, inf,  68,  49,  51,  57, inf, inf,  61,  74, inf, inf},
      { 40,  58, inf,  60,  41,  43,  49, inf, inf,  53,  66, inf,   0}
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
  std::vector<int> got;
  auto [coste, camino] = Laberinto<int>(5, muros, 2, 22);
  for (auto it = camino.primera(); it != camino.fin();
       it = camino.siguiente(it)) {
    got.push_back(camino.elemento(it));
  }
  ASSERT_EQ(10, coste);
  ASSERT_THAT(got, ElementsAreArray({2, 1, 6, 11, 12, 13, 18, 17, 16, 21, 22}));
}

TEST_F(Practica_7, ejercico_3_distribucion) {
  GrafoP<unsigned> G("files/grafos/distribucion.txt");
  auto [dist, coste] = Distribucion<unsigned>(G, 1, 80, {20, 0, 10, 50, 40, 10},
                                              {30, 0, 25, 15, 10, 20});
  ASSERT_EQ(23u, coste);
  ASSERT_THAT(dist, ElementsAreArray<unsigned>({20, 0, 10, 0, 0, 10}));
}

TEST_F(Practica_7, ejercicio_4_cementos_zuelandia) {
  GrafoP<short> G("files/grafos/zuelandia.txt");
  vector<short> diario{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  EXPECT_EQ(419, CementosZuelandia(G, 0, diario));
}

TEST_F(Practica_7, ejercicio_5_alergia) {
  GrafoP<short> A("files/grafos/p7-5-a.txt");
  GrafoP<short> C("files/grafos/p7-5-c.txt");
  GrafoP<short> T("files/grafos/p7-5-t.txt");
  short presupuesto{50};
  vector<vector<short>> got(3);
  got[0] = Alergico(C, A, T, presupuesto, 0, 0);
  got[1] = Alergico(C, A, T, presupuesto, 1, 0);
  got[2] = Alergico(C, A, T, presupuesto, 2, 0);
  ASSERT_THAT(got, ElementsAreArray({vector<short>{1, 2, 3, 4, 11, 12},
                                     vector<short>{4, 11, 12},
                                     vector<short>{1, 2, 3, 4, 5, 6, 11, 12}}));
}

TEST_F(Practica_7, ejercicio_6_agencia_transporte_sin_taxi) {
  GrafoP<int> B("files/grafos/bus.txt");
  GrafoP<int> T("files/grafos/tren.txt");
  vector<vector<int>> F_min =
      static_cast<vector<vector<int>>>(AgenciaTransporteSinTaxi(B, T, 4));
  ASSERT_THAT(
      F_min, ElementsAreArray<vector<int>>({{0, 77, 13, 11, 64, 32, 91, 57},
                                            {77, 0, 31, 59, 30, 62, 87, 50},
                                            {13, 31, 0, 57, 47, 78, 70, 101},
                                            {11, 59, 57, 0, 53, 21, 110, 9},
                                            {64, 30, 47, 53, 0, 32, 57, 54},
                                            {32, 62, 78, 21, 32, 0, 89, 54},
                                            {91, 92, 70, 115, 57, 94, 0, 111},
                                            {57, 50, 102, 9, 54, 54, 111, 0}}));
}

TEST_F(Practica_7, ejercicio_7_transporte_sin_taxi_dos_estaciones) {
  GrafoP<int> B("files/grafos/bus.txt");
  GrafoP<int> T("files/grafos/tren.txt");
  vector<int> got;
  auto [coste, camino] = TransporteSinTaxiDosEstaciones(T, B, 0, 7, 4, 3);
  for (auto it = camino.primera(); it != camino.fin();
       it = camino.siguiente(it)) {
    got.push_back(camino.elemento(it));
  }
  ASSERT_EQ(coste, 126);
  ASSERT_THAT(got, ElementsAreArray({0, 3, 7}));
}

TEST_F(Practica_7, ejercicio_7_transporte_sin_taxi_dos_estaciones_2) {
  GrafoP<int> B("files/grafos/bus.txt");
  GrafoP<int> T("files/grafos/tren.txt");
  vector<int> got;
  auto [coste, camino] = TransporteSinTaxiDosEstaciones(T, B, 1, 6, 4, 3);
  for (auto it = camino.primera(); it != camino.fin();
       it = camino.siguiente(it)) {
    got.push_back(camino.elemento(it));
  }
  ASSERT_EQ(coste, 123);
  ASSERT_THAT(got, ElementsAreArray({1, 4, 6}));
}

TEST_F(Practica_7, ejercicio_8_un_solo_transbordo) {
  GrafoP<int> B("files/grafos/bus.txt");
  GrafoP<int> T("files/grafos/tren.txt");
  int coste{UnSoloTransbordo(T, B, 0, 7)};
  ASSERT_EQ(20, coste);
}

TEST_F(Practica_7, ejercicio_9_transporte_con_taxi) {
  GrafoP<int> B("files/grafos/bus.txt");
  GrafoP<int> T("files/grafos/tren.txt");
  vector<int> got;
  auto [coste, camino] = TransporteConTaxi(B, T, 0, 1);
  for (auto it = camino.primera(); it != camino.fin();
       it = camino.siguiente(it)) {
    got.push_back(camino.elemento(it));
  }
  ASSERT_EQ(coste, 45);
  ASSERT_THAT(got, ElementsAreArray({0, 2, 2, 1}));
}

TEST_F(Practica_7, ejercicio_9_transporte_con_taxi2) {
  GrafoP<int> B("files/grafos/bus.txt");
  GrafoP<int> T("files/grafos/tren.txt");
  vector<int> got;
  auto [coste, camino] = TransporteConTaxi(B, T, 0, 7);
  for (auto it = camino.primera(); it != camino.fin();
       it = camino.siguiente(it)) {
    got.push_back(camino.elemento(it));
  }
  ASSERT_EQ(coste, 22);
  ASSERT_THAT(got, ElementsAreArray({0, 0, 3, 3, 7}));
}