#include "op.hpp"

Op::Op(double opd = 0, char opr = '_') : operando{opd}, operador{opr} {}

std::ostream &operator<<(std::ostream &os, const Op &op) {
  if (op.operando != '_') {
    os << op.operador;
  }
  os << op.operando;
  return os;
}