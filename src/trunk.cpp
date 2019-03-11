#include "trunk.hpp"
Trunk::Trunk(Trunk *prev, std::string str): _prev(prev), _str(str) {}

void showTrunks(std::ostream &os, Trunk *p) {
  if (p == nullptr) {
    return;
  }
  showTrunks(os, p->_prev);
  os << p->_str;
}