#include "abin_p1.hpp"
#include "op.hpp"
#include "ioabin.hpp"
#include <fstream>
#include <gtest/gtest.h>

using namespace Enlazada;

class Abin_1 : public ::testing::Test {
protected:
  void SetUp() override {
    std::ifstream is("files/abin.txt", std::ifstream::binary);
    is >> A_;
    is.close();
  }
  Abin<char> A_;
};

TEST_F(Abin_1, count_abin_nodes) { EXPECT_EQ(12, nodos(A_)); }

TEST_F(Abin_1, altura_abin) { EXPECT_EQ(4, altura(A_)); }

TEST_F(Abin_1, profundidad_abin_raiz) {
  EXPECT_EQ(0, profundidad(A_, A_.raizB()));
}

TEST_F(Abin_1, profundidad_abin_nodo) {
  auto nodo =
      A_.hijoIzqdoB(A_.hijoDrchoB(A_.hijoDrchoB(A_.hijoDrchoB(A_.raizB()))));
  EXPECT_EQ(4, profundidad(A_, nodo));
}

TEST_F(Abin_1, desequilibrio_abin_raiz) { EXPECT_EQ(2, desequilibrio(A_)); }

TEST_F(Abin_1, isFullTree_abin_false) { EXPECT_FALSE(isFullTree(A_)); }

TEST_F(Abin_1, isFullTree_abin_empty) {
  Abin<char> E;
  EXPECT_FALSE(isFullTree(E));
}

TEST(Abin_1_1, isFullTree_abin_true) {
  Abin<char> P_;
  std::ifstream is("files/pseudocmp.txt", std::ifstream::binary);
  is >> P_;
  is.close();
  EXPECT_TRUE(isFullTree(P_));
}

TEST(Abin_1_1, isFullTree_ful_true) {
  Abin<char> P_;
  std::ifstream is("files/complete.txt", std::ifstream::binary);
  is >> P_;
  is.close();
  EXPECT_TRUE(isFullTree(P_));
}

TEST(Abin_1_1, isFullTree_abin_operacion) {
  Abin<Op> P_;
  std::ifstream is("files/op.txt", std::ifstream::binary);
  is >> P_;
  is.close();
  EXPECT_TRUE(isFullTree(P_));
}