#ifndef LISTA_HPP
#define LISTA_HPP
namespace grafos {
template <typename T>
class Lista {
  struct nodo;

 public:
  using posicion = nodo*;
  Lista() : L{new nodo(T())} {}
  Lista(const Lista<T>& l) { copiar(l); }
  Lista<T>& operator=(const Lista<T>& l);
  Lista<T>& operator+=(const Lista<T>& l);
  void insertar(const T& x, posicion p);
  void eliminar(posicion p);
  const T& elemento(posicion p) const;
  T& elemento(posicion p);
  posicion buscar(const T& x) const;
  posicion siguiente(posicion p) const;
  posicion anterior(posicion p) const;
  posicion primera() const { return L; }
  posicion fin() const;
  ~Lista();

 private:
  struct nodo {
    T elto;
    nodo* sig;
    nodo(const T& e, nodo* p = nullptr) : elto(e), sig(p) {}
  };
  nodo* L;
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