#ifndef AFIG_HPP
#define AFIG_HPP
#include "agen.hpp"
#include "ioagen.hpp"
#include <fstream>
#include <vector>
class Afig {
public:
  enum NODOS { BLANCO = 'B', NEGRO = 'N', VACIO = 'V' };
  Afig();
  friend std::ifstream &operator>>(std::ifstream &ifs, Agen<char> &a);
  std::vector<std::vector<char>> figura() const;

private:
  Agen<char> arbol;
};

std::ifstream &operator>>(std::ifstream &ifs, Afig<char> &a) {
  ifs >> a.arbol;
  return ifs;
}
#endif
