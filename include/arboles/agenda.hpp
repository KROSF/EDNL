#ifndef AGENDA_HPP
#define AGENDA_HPP
#include <string>
#include "abb.hpp"

class Contacto {
 public:
  Contacto(const std::string &nom, unsigned num) : nombre{nom}, numero{num} {}
  std::string nombre;
  unsigned numero;
};

bool operator<(const Contacto &a, const Contacto &b) {
  return a.nombre < b.nombre;
}

bool operator>(const Contacto &a, const Contacto &b) {
  return a.nombre > b.nombre;
}

bool operator==(const Contacto &a, const Contacto &b) {
  return a.nombre == b.nombre;
}

class Agenda {
 public:
  Agenda();
  void insertar(const Contacto &c) { agenda.insertar(c); }
  void eliminar(const Contacto &c) { agenda.eliminar(c); }
  Contacto buscar(const Contacto &c) {
    Abb<Contacto> found = agenda.buscar(c);
    return (!found.vacio()) ? found.elemento() : Contacto("No Encontrado", 0);
  }

 private:
  Abb<Contacto> agenda;
};
#endif