#include <gtest/gtest.h>
#include "abin_p1.hpp"
#include "ioabin.hpp"
#include <fstream>

using namespace Vectorial;

TEST(Practica_2, count_tree_nodes) {
  Abin<char> A(100);
  std::ifstream is("abin.txt",
                   std::ifstream::binary);
  is >> A;
  EXPECT_EQ(12, nodos(A));
}