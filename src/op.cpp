#include "arboles/op.hpp"
#include <string>

Op::Op(double opd, char opr) : operando{opd}, operador{opr} {}

std::ostream &operator<<(std::ostream &os, const Op &op) {
  if (op.operador != '_') {
    os << op.operador;
  } else {
    os << op.operando;
  }
  return os;
}

std::istream &operator>>(std::istream &is, Op &op) {
  std::string in;
  is >> in;
  if (in == "+" || in == "-" || in == "/" || in == "*" || in == "#") {
    op.operador = in[0];
  } else {
    op.operando = std::stod(in);
  }
  return is;
}

bool operator!=(const Op &op1, const Op &op2) {
  if (op1.operador != op2.operador && op1.operando == op2.operando) {
    return true;
  }
  return op1.operador != op2.operador && op1.operando != op2.operando;
}