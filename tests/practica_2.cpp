#include "abin_p2.hpp"
#include "ioabin.hpp"
#include "pathabin.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <sstream>

using namespace Enlazada;

class Abin_2 : public ::testing::Test {
protected:
  void SetUp() override {
    std::ifstream isA("abin.txt", std::ifstream::binary);
    std::ifstream isB("pseudocmp.txt", std::ifstream::binary);
    isA >> A_;
    isB >> B_;
    isA.close();
    isB.close();
  }
  Abin<char> A_;
  Abin<char> B_;
};
TEST_F(Abin_2, similar_tree_true) {
  Abin<char> C_{A_};
  EXPECT_TRUE(A_ ^ C_);
}

TEST_F(Abin_2, similar_tree_false) { EXPECT_FALSE(A_ ^ B_); }

TEST_F(Abin_2, similar_tree_empty_true) {
  Abin<char> eA, eB;
  EXPECT_TRUE(eA ^ eB);
}

TEST_F(Abin_2, similar_tree_empty_false) {
  Abin<char> eA;
  EXPECT_FALSE(A_ ^ eA);
}

TEST_F(Abin_2, reflejo_abin) {
  Abin<char> rA{reflejo(A_)};
  std::string srA;
  preOrder<char>(rA, rA.raizB(), [&srA](Abin<char> &a, const Nodo<char> &n) {
    srA += a.elemento(n);
  });
  EXPECT_EQ("agikljhbefcd", srA);
}

TEST_F(Abin_2, reflejo_pseudocmp) {
  Abin<char> rB{reflejo(B_)};
  std::string srB;
  preOrder<char>(rB, rB.raizB(), [&srB](Abin<char> &a, const Nodo<char> &n) {
    srB += a.elemento(n);
  });
  EXPECT_EQ("agikmljhbefcd", srB);
}

TEST(Abin_2_1, operacion_ostream_operando) {
  Op op;
  std::ostringstream stream;
  stream << op;
  EXPECT_EQ("0", stream.str());
}

TEST(Abin_2_1, operacion_ostream_operador) {
  Op op(0, '+');
  std::ostringstream stream;
  stream << op;
  EXPECT_EQ("+", stream.str());
}

TEST(Abin_2_1, operacion) {
  Abin<Op> OP;
  std::ifstream is("op.txt", std::ifstream::binary);
  is >> OP;
  is.close();
  EXPECT_DOUBLE_EQ(178, operacion(OP));
}
