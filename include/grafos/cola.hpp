#ifndef COLA_HPP
#define COLA_HPP
#include <cassert>
namespace grafos {
template <typename T>
class Cola {
 public:
  Cola() : inicio{nullptr}, fin{nullptr} {}
  Cola(const Cola<T>& c) : inicio{nullptr}, fin{nullptr} { copiar(c); }
  Cola<T>& operator=(const Cola<T>& c) {
    if (this != &c) {
      this->~Cola();
      copiar(c);
    }
  }
  bool vacia() const { return inicio == nullptr; }
  const T& frente() const;
  void pop();
  void push(const T& x);
  ~Cola();

 private:
  struct nodo {
    T elto;
    nodo* sig;
    nodo(const T& e, nodo* p = nullptr) : elto{e}, sig{p} {}
  };
  nodo* inicio;
  nodo* fin;
  void copiar(const Cola<T>&);
};

template <typename T>
void Cola<T>::copiar(const Cola<T>& c) {
  if (c.inicio) {
    inicio = fin = new nodo(c.inicio->elto);
    for (nodo* p = c.inicio->sig; p; p = p->sig) {
      fin->sig = new nodo(p->elto);
      fin = fin->sig;
    }
  }
}

template <typename T>
inline const T& Cola<T>::frente() const {
  assert(!vacia());
  return inicio->elto;
}

template <typename T>
inline void Cola<T>::pop() {
  assert(!vacia());
  nodo* p{inicio};
  inicio = p->sig;
  if (!inicio) fin = 0;
  delete p;
}

template <typename T>
inline void Cola<T>::push(const T& x) {
  nodo* p{new nodo(x)};
  if (inicio == 0)
    inicio = fin = p;
  else
    fin = fin->sig = p;
}

template <typename T>
Cola<T>::~Cola() {
  nodo* p;
  while (inicio) {
    p = inicio->sig;
    delete inicio;
    inicio = p;
  }
  fin = 0;
}

}  // namespace grafos
#endif