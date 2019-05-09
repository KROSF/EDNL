#include <gtest/gtest.h>
#include <fstream>
#include "arboles/abin_p1.hpp"
#include "arboles/ioabin.hpp"
#include "arboles/op.hpp"

using namespace Enlazada;

class Practica_1 : public ::testing::Test {
 protected:
  void SetUp() override {
    std::ifstream is("files/abin.txt", std::ifstream::binary);
    is >> A_;
    is.close();
  }
  Abin<char> A_;
};

TEST_F(Practica_1, ejercicio_1_nodos) { EXPECT_EQ(12, nodos(A_)); }

TEST_F(Practica_1, ejercicio_2_altura) { EXPECT_EQ(4, altura(A_)); }

TEST_F(Practica_1, ejercicio_3_profundidad_raiz) {
  EXPECT_EQ(0, profundidad(A_, A_.raizB()));
}

TEST_F(Practica_1, ejercicio_3_profundidad_max) {
  auto nodo =
      A_.hijoIzqdoB(A_.hijoDrchoB(A_.hijoDrchoB(A_.hijoDrchoB(A_.raizB()))));
  EXPECT_EQ(4, profundidad(A_, nodo));
}

TEST_F(Practica_1, ejercicio_6_desequilibrio) {
  EXPECT_EQ(2, desequilibrio(A_));
}

TEST_F(Practica_1, ejercicio_7_pseudocompleto_false) {
  EXPECT_FALSE(isFullTree(A_));
}

TEST_F(Practica_1, ejercicio_7_pseudocompleto_false_empty) {
  Abin<char> E;
  EXPECT_FALSE(isFullTree(E));
}

TEST_F(Practica_1, ejercicio_7_pseudocompleto_true) {
  Abin<char> P_;
  std::ifstream is("files/pseudocmp.txt", std::ifstream::binary);
  is >> P_;
  is.close();
  EXPECT_TRUE(isFullTree(P_));
}

TEST_F(Practica_1, ejercicio_7_pseudocompleto_true_2) {
  Abin<char> P_;
  std::ifstream is("files/complete.txt", std::ifstream::binary);
  is >> P_;
  is.close();
  EXPECT_TRUE(isFullTree(P_));
}

TEST_F(Practica_1, ejercicio_7_pseudocompleto_true_3) {
  Abin<Op> P_;
  std::ifstream is("files/op.txt", std::ifstream::binary);
  is >> P_;
  is.close();
  EXPECT_TRUE(isFullTree(P_));
}