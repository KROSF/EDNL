#ifndef OP_HPP
#define OP_HPP
#include <ostream>
struct Op {
  double operando;
  char operador;
  Op(double opd = 0, char opr = '_');
};
std::ostream &operator<<(std::ostream &, const Op &);
#endif