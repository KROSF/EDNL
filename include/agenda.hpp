#ifndef AGENDA_HPP
#define AGENDA_HPP
#include "abb.hpp"
#include <string>

class Contacto {
public:
  Contacto(std::string nom, unsigned num) : nombre{nom}, num{numero} {}
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