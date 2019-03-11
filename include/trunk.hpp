#ifndef TRUNK_HPP
#define TRUNK_HPP
#include <ostream>
#include <string>
struct Trunk {
  Trunk(Trunk *prev, std::string str);
  Trunk *_prev;
  std::string _str;
};

void showTrunks(std::ostream &os, Trunk *p);
#endif