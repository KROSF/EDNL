#ifndef LISTA_HPP
#define LISTA_HPP
#include <cassert>
namespace grafos {
template <typename T>
// Lista Dinamica Simplemente Enlazada
class Lista {
  // Nodos de la lista.
  struct nodo;

 public:
  // Posicion de un nodo en la lista.
  using posicion = nodo*;
  // Crea una lista vacia.
  Lista() : L{new nodo(T())} {}
  // Crea una copia de una lista.
  Lista(const Lista<T>& l) { copiar(l); }
  Lista<T>& operator=(const Lista<T>& l);
  Lista<T>& operator+=(const Lista<T>& l);
  // Inserta un elemento en posicion de la lista.
  void insertar(const T& x, posicion p);
  // Elimina la posicion del elemento.
  void eliminar(posicion p);
  // Devuelve el elemento en la posicion.
  const T& elemento(posicion p) const;
  // Devuelve una referencia del elemento en la posicion.
  T& elemento(posicion p);
  // Devuelve la posicion de un elemento
  posicion buscar(const T& x) const;
  // Devuelve la posicion siguiente a p.
  posicion siguiente(posicion p) const;
  // Devuelve la posicion anterior a p.
  posicion anterior(posicion p) const;
  // Devuelve la primera posicion de la lista.
  posicion primera() const { return L; }
  // Devuelve la posicion siguiente a la ultima.
  posicion fin() const;
  // Destruye la lista.
  ~Lista();

 private:
  struct nodo {
    // Elemento en el nodo.
    T elto;
    // Siguiente nodo.
    nodo* sig;
    // Constructor de nodo.
    nodo(const T& e, nodo* p = nullptr) : elto(e), sig(p) {}
  };
  // Lista de nodos.
  nodo* L;
  // Copia una lista en otra.
  void copiar(const Lista<T>& l);
};

template <typename T>
void Lista<T>::copiar(const Lista<T>& l) {
  L = new nodo(T());
  nodo* q = L;
  for (nodo* r = l.L->sig; r; r = r->sig) {
    q->sig = new nodo(r->elto);
    q = q->sig;
  }
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& l) {
  if (this != &l) {
    this->~Lista();
    copiar(l);
  }
  return *this;
}

template <typename T>
inline void Lista<T>::insertar(const T& x, Lista<T>::posicion p) {
  p->sig = new nodo(x, p->sig);
}

template <typename T>
inline void Lista<T>::eliminar(Lista<T>::posicion p) {
  assert(p->sig);
  nodo* q = p->sig;
  p->sig = q->sig;
  delete q;
}

template <typename T>
inline const T& Lista<T>::elemento(Lista<T>::posicion p) const {
  assert(p->sig);
  return p->sig->elto;
}

template <typename T>
inline T& Lista<T>::elemento(Lista<T>::posicion p) {
  assert(p->sig);
  return p->sig->elto;
}

template <typename T>
typename Lista<T>::posicion Lista<T>::buscar(const T& x) const {
  nodo* q{L};
  bool encontrado = false;
  while (q->sig && !encontrado)
    if (q->sig->elto == x)
      encontrado = true;
    else
      q = q->sig;
  return q;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::siguiente(
    Lista<T>::posicion p) const {
  assert(p->sig);
  return p->sig;
}

template <typename T>
typename Lista<T>::posicion Lista<T>::anterior(Lista<T>::posicion p) const {
  nodo* q;
  assert(p != L);
  for (q = L; q->sig != p; q = q->sig)
    ;
  return q;
}

template <typename T>
typename Lista<T>::posicion Lista<T>::fin() const {
  nodo* p;
  for (p = L; p->sig; p = p->sig)
    ;
  return p;
}

template <typename T>
Lista<T>::~Lista() {
  nodo* q;
  while (L) {
    q = L->sig;
    delete L;
    L = q;
  }
}
template <typename T>
Lista<T>& Lista<T>::operator+=(const Lista<T>& l) {
  for (Lista<T>::posicion i = l.primera(); i != l.fin(); i = l.siguiente(i))
    insertar(l.elemento(i), fin());
  return *this;
}

template <typename T>
Lista<T> operator+(const Lista<T>& l1, const Lista<T>& l2) {
  return Lista<T>(l1) += l2;
}

}  // namespace grafos
#endif