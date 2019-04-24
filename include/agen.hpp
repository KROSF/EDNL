#ifndef AGEN_HPP
#define AGEN_HPP
#include <cassert>
namespace Enlazada {

template <typename T> class Agen {
  struct Celda;

public:
  using Nodo = Celda *;
  inline static const Nodo NODO_NULO = nullptr;

  Agen() : _raiz{NODO_NULO} {}
  Agen(const Agen<T> &a) : _raiz{copiar(a._raiz)} {}
  void insertarRaiz(const T &e);
  void insertarHijoIzqdo(Nodo n, const T &e);
  void insertarHermDrcho(Nodo n, const T &e);
  void eliminarHijoIzqdo(Nodo n);
  void eliminarHermDrcho(Nodo n);
  void eliminarRaiz();
  bool arbolVacio() const { return _raiz == nullptr; }
  const T &elemento(Nodo n) const;
  T &elemento(Nodo n);
  Nodo raiz() const { return _raiz; }
  Nodo padre(Nodo n) const;
  Nodo hijoIzqdo(Nodo n) const;
  Nodo hermDrcho(Nodo n) const;
  Agen<T> &operator=(const Agen<T> &a);
  ~Agen() { destruirNodos(_raiz); }

private:
  struct Celda {
    T elto;
    Nodo padre, hizq, hedch;
    Celda(const T &e, Nodo p = NODO_NULO)
        : elto{e}, padre{p}, hizq{NODO_NULO}, hedch{NODO_NULO} {}
  };
  Nodo _raiz;
  void destruirNodos(Nodo &n);
  Nodo copiar(Nodo n);
};

template <typename T> void Agen<T>::destruirNodos(Nodo &n) {
  if (n != NODO_NULO) {
    if (n->hizq != NODO_NULO) {
      Nodo hedrcho = n->hizq->hedch;
      while (hedrcho != NODO_NULO) {
        n->hizq->hedch = hedrcho->hedch;
        destruirNodos(hedrcho);
        hedrcho = n->hizq->hedch;
      }
      destruirNodos(n->hizq);
    }
    delete n;
    n = NODO_NULO;
  }
}

template <typename T> typename Agen<T>::Nodo Agen<T>::copiar(Nodo n) {
  Nodo m = NODO_NULO;
  if (n != NODO_NULO) {
    m = new Celda(n->elto);
    if (n->hizq != NODO_NULO) {
      m->hizq = copiar(n->hizq);
      m->hizq->padre = m;
      Nodo hijo = m->hizq;
      Nodo hedrcho = n->hizq->hedch;
      while (hedrcho != NODO_NULO) {
        hijo = hijo->hedch = copiar(hedrcho);
        hijo->padre = m;
        hedrcho = hedrcho->hedch;
      }
    }
  }
  return m;
}

template <typename T> inline void Agen<T>::insertarRaiz(const T &e) {
  assert(_raiz == NODO_NULO);
  _raiz = new Celda(e);
}

template <typename T>
inline void Agen<T>::insertarHijoIzqdo(Nodo n, const T &e) {
  assert(n != NODO_NULO);
  Nodo hizqdo = n->hizq;
  n->hizq = new Celda(e, n);
  n->hizq->hedch = hizqdo;
}

template <typename T>
inline void Agen<T>::insertarHermDrcho(Nodo n, const T &e) {
  assert(n != NODO_NULO);
  assert(n != _raiz);
  Nodo hedrcho = n->hedch;
  n->hedch = new Celda(e, n->padre);
  n->hedch->hedch = hedrcho;
}

template <typename T> inline void Agen<T>::eliminarHijoIzqdo(Nodo n) {
  Nodo hizqdo{n->hizq};
  assert(n != NODO_NULO);
  assert(hizqdo != NODO_NULO);
  assert(hizqdo->hizq == NODO_NULO);
  n->hizq = hizqdo->hedch;
  delete hizqdo;
}

template <typename T> inline void Agen<T>::eliminarHermDrcho(Nodo n) {
  Nodo hedrcho{n->hedch};
  assert(n != NODO_NULO);
  assert(hedrcho != NODO_NULO);
  assert(hedrcho->hizq == NODO_NULO);
  n->hedch = hedrcho->hedch;
  delete hedrcho;
}

template <typename T> inline void Agen<T>::eliminarRaiz() {
  assert(_raiz != NODO_NULO);
  assert(_raiz->hizq == NODO_NULO);
  delete _raiz;
  _raiz = NODO_NULO;
}

template <typename T> inline const T &Agen<T>::elemento(Nodo n) const {
  assert(n != NODO_NULO);
  return n->elto;
}

template <typename T> inline T &Agen<T>::elemento(Nodo n) {
  assert(n != NODO_NULO);
  return n->elto;
}

template <typename T>
inline typename Agen<T>::Nodo Agen<T>::padre(Nodo n) const {
  assert(n != NODO_NULO);
  return n->padre;
}

template <typename T>
inline typename Agen<T>::Nodo Agen<T>::hijoIzqdo(Nodo n) const {
  assert(n != NODO_NULO);
  return n->hizq;
}

template <typename T>
inline typename Agen<T>::Nodo Agen<T>::hermDrcho(Nodo n) const {
  assert(n != NODO_NULO);
  return n->hedch;
}

template <typename T> Agen<T> &Agen<T>::operator=(const Agen<T> &a) {
  if (this != &a) {
    this->~Agen();
    _raiz = copiar(a._raiz);
  }
  return *this;
}

} // namespace Enlazada
#endif