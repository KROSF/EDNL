#ifndef OP_HPP
#define OP_HPP
#include <iostream>
struct Op {
  double operando;
  char operador;
  Op(double opd = 0, char opr = '_');
};
bool operator!=(const Op &, const Op &);
std::ostream &operator<<(std::ostream &, const Op &);
std::istream &operator>>(std::istream &, Op &);
#endif