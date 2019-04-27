#include "abb.hpp"
#include "abb_px.hpp"
#include "ioabin.hpp"
#include <fstream>
#include <gtest/gtest.h>

class Practica_4 : public ::testing::Test {
  Enlazada::Abin<char> A, B;

protected:
  void SetUp() override {
    std::ifstream isa("files/abin.txt", std::ifstream::binary);
    std::ifstream isb("files/abb.txt", std::ifstream::binary);
    isa >> A;
    isb >> B;
    isb.close();
    isa.close();
    a = A;
    b = B;
    equilibrar(b);
    equilibrar(a);
  }
  Abb<char> a, b;
};

TEST_F(Practica_4, ejercicio_1_poda) {
Enlazada::Abin<int> aint;
  std::ifstream isa("files/abb_poda.txt", std::ifstream::binary);
  isa >> aint;
  Abb<int> abbint{aint};
  abbint.podar(9);
  std::string s;
  inOrder<int>(abbint, [&s](const Abb<int> &e) { s += std::to_string(e.elemento()); });
  EXPECT_EQ("571217", s);
}

TEST_F(Practica_4, ejercicio_4_union) {
  auto unio = unionAbb(a, b);
  std::string s;
  inOrder<char>(unio, [&s](const Abb<char> &e) { s += e.elemento(); });
  EXPECT_EQ("abcdefghijklmoqrsz", s);
}

TEST_F(Practica_4, ejercicio_5_interseccion) {
  auto unio = interseccionAbb(a, b);
  std::string s;
  inOrder<char>(unio, [&s](const Abb<char> &e) { s += e.elemento(); });
  EXPECT_EQ("bdfikl", s);
}

TEST_F(Practica_4, ejercicio_6_diferencia) {
  auto unio = diferenciaAbb(a, b);
  std::string s;
  inOrder<char>(unio, [&s](const Abb<char> &e) { s += e.elemento(); });
  EXPECT_EQ("aceghj", s);
}

TEST_F(Practica_4, ejercicio_6_operadorRombo) {
  auto unio = operadorRombo(a, b);
  std::string s;
  inOrder<char>(unio, [&s](const Abb<char> &e) { s += e.elemento(); });
  EXPECT_EQ("aceghjmoqrsz", s);
}