#include "agen_p1.hpp"
#include "ioagen.hpp"
#include <fstream>
#include <gtest/gtest.h>
using namespace Enlazada;
class Practica_3 : public ::testing::Test {
protected:
  void SetUp() override {
    std::ifstream is("files/agen.txt", std::ifstream::binary);
    is >> A_;
    is.close();
  }
  Agen<char> A_;
};

TEST_F(Practica_3, ejercicio_1_grado) { EXPECT_EQ(4, grado(A_)); }

TEST_F(Practica_3, ejercicio_2_profundidad) {
  auto n = A_.hijoIzqdo(
      A_.hijoIzqdo(A_.hermDrcho(A_.hermDrcho(A_.hijoIzqdo(A_.raiz())))));
  EXPECT_EQ(3, profundidad(A_, n));
}

TEST_F(Practica_3, ejercicio_3_desequilibrio) {
  EXPECT_EQ(1, desequilibrio(A_));
}