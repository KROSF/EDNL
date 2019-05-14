#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "arboles/abin_p2.hpp"
#include "arboles/ioabin.hpp"
#include "arboles/pathabin.hpp"

using namespace Enlazada;

class Practica_2 : public ::testing::Test {
 protected:
  void SetUp() override {
    std::ifstream isA("files/arboles/abin.txt", std::ifstream::binary);
    std::ifstream isB("files/arboles/pseudocmp.txt", std::ifstream::binary);
    isA >> A_;
    isB >> B_;
    isA.close();
    isB.close();
  }
  Abin<char> A_;
  Abin<char> B_;
};
TEST_F(Practica_2, ejercicio_1_similares_true) {
  Abin<char> C_{A_};
  EXPECT_TRUE(A_ ^ C_);
}

TEST_F(Practica_2, ejercicio_1_similares_false) { EXPECT_FALSE(A_ ^ B_); }

TEST_F(Practica_2, ejercicio_1_similares_true_empty) {
  Abin<char> eA, eB;
  EXPECT_TRUE(eA ^ eB);
}

TEST_F(Practica_2, ejercicio_1_similares_false_empty) {
  Abin<char> eA;
  EXPECT_FALSE(A_ ^ eA);
}

TEST_F(Practica_2, ejercicio_2_reflejado) {
  Abin<char> rA{reflejo(A_)};
  std::string srA;
  preOrder<char>(rA, rA.raizB(), [&srA](Abin<char> &a, const Nodo<char> &n) {
    srA += a.elemento(n);
  });
  EXPECT_EQ("agikljhbefcd", srA);
}

TEST_F(Practica_2, ejercicio_2_reflejado_2) {
  Abin<char> rB{reflejo(B_)};
  std::string srB;
  preOrder<char>(rB, rB.raizB(), [&srB](Abin<char> &a, const Nodo<char> &n) {
    srB += a.elemento(n);
  });
  EXPECT_EQ("agikmljhbefcd", srB);
}

TEST_F(Practica_2, operacion_ostream_operando) {
  Op op;
  std::ostringstream stream;
  stream << op;
  EXPECT_EQ("0", stream.str());
}

TEST_F(Practica_2, operacion_ostream_operador) {
  Op op(0, '+');
  std::ostringstream stream;
  stream << op;
  EXPECT_EQ("+", stream.str());
}

TEST_F(Practica_2, ejercico_3_operacion_arimetica) {
  Abin<Op> OP;
  std::ifstream is("files/arboles/op.txt", std::ifstream::binary);
  is >> OP;
  is.close();
  EXPECT_DOUBLE_EQ(178, operacion(OP));
}
