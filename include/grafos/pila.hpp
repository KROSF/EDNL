#ifndef PILA_HPP
#define PILA_HPP
#include <cassert>
namespace grafos {
template <typename T>
// Pila dinamica
class Pila {
 public:
  // Crea una Pila vacia.
  Pila() : tope_{nullptr} {}
  // Crea una copia de la pila P.
  Pila(const Pila<T>& P) : tope_{nullptr} { copiar(P); }
  Pila<T>& operator=(const Pila<T>& P);
  // Devuelve true si la pila esta vacia.
  bool vacia() const { return !tope_; }
  // Devuelve el elemento en el tope de la pila.
  const T& tope() const;
  // Elimina el elemento en el tope de la pila.
  void pop();
  // Inserta un elemento en el tope de la pila.
  void push(const T& x) { tope_ = new nodo(x, tope_); }
  // Destruye la pila.
  ~Pila();

 private:
  // nodos que conforman una pila.
  struct nodo {
    // Elemento almacenado en un nodo de la pila.
    T elto;
    // puntero al siguiente nodo.
    nodo* sig;
    // Constructor de nodos.
    nodo(const T& e, nodo* p = nullptr) : elto(e), sig(p) {}
  };
  nodo* tope_;
  // Copia los elementos de una pila a otra.
  void copiar(const Pila<T>& P);
};

template <typename T>
Pila<T>& Pila<T>::operator=(const Pila<T>& P) {
  if (this != &P) {
    this->~Pila();
    copiar(P);
  }
  return *this;
}

template <typename T>
inline const T& Pila<T>::tope() const {
  assert(!vacia());
  return tope_->elto;
}

template <typename T>
inline void Pila<T>::pop() {
  assert(!vacia());
  nodo* p = tope_;
  tope_ = p->sig;
  delete p;
}

template <typename T>
Pila<T>::~Pila() {
  nodo* p;
  while (tope_) {
    p = tope_->sig;
    delete tope_;
    tope_ = p;
  }
}

template <typename T>
void Pila<T>::copiar(const Pila<T>& P) {
  if (!P.vacia()) {
    tope_ = new nodo(P.tope());
    nodo* p = tope_;
    nodo* q = P.tope_->sig;
    while (q) {
      p->sig = new nodo(q->elto);
      p = p->sig;
      q = q->sig;
    }
  }
}

}  // namespace grafos
#endif