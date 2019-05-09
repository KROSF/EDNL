#ifndef COLA_HPP
#define COLA_HPP
#include <cassert>
namespace grafos {
template <typename T>
// Cola Dinamica
class Cola {
 public:
  // Crea una cola vacia.
  Cola() : inicio{nullptr}, fin{nullptr} {}
  // Crea una copia de la cola c.
  Cola(const Cola<T>& c) : inicio{nullptr}, fin{nullptr} { copiar(c); }
  Cola<T>& operator=(const Cola<T>& c) {
    if (this != &c) {
      this->~Cola();
      copiar(c);
    }
  }
  // Comprueba si la cola esta vacia.
  bool vacia() const { return inicio == nullptr; }
  // Devuelve el primer elemento de la cola.
  const T& frente() const;
  // Elimina el primer elemento de la cola.
  void pop();
  // Insertar un elemento al final de la cola.
  void push(const T& x);
  // Destruye la cola.
  ~Cola();

 private:
  // Estrutura de elementos de la cola.
  struct nodo {
    // Elemento almacenado en la cola.
    T elto;
    // Nodo siguiente.
    nodo* sig;
    // Constructor de nodos.
    nodo(const T& e, nodo* p = nullptr) : elto{e}, sig{p} {}
  };
  // Inicio de la cola.
  nodo* inicio;
  // Fin de la cola.
  nodo* fin;
  // Metodo privado para copiar una cola.
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