#ifndef ABB_HPP
#define ABB_HPP
#include "abin.hpp"
#include <cassert>
template <typename T> class Abb {
public:
  Abb() : raiz{nullptr} {}
  Abb(const Enlazada::Abin<T> &a) : raiz{nullptr} { copiar(a, a.raizB()); }
  const Abb &buscar(const T &e) const;
  void insertar(const T &e);
  void eliminar(const T &e);
  void podar(const T &);
  bool vacio() const { return raiz == nullptr; }
  const T &elemento() const;
  const Abb &izquierdo() const;
  const Abb &derecho() const;
  operator Enlazada::Abin<T>() const;
  Abb(const Abb &a);
  Abb &operator=(const Abb &a);
  ~Abb();

private:
  struct Nodo {
    T elto;
    Abb izq, dch;
    Nodo(const T &e) : elto{e} {}
  };
  Nodo *raiz;
  T borrarMin();
  void copiar(const Abb &a);
  void copiar(const Enlazada::Abin<T> &a, typename Enlazada::Abin<T>::Nodo n);
  void copiarAbb(Enlazada::Abin<T> &, typename Enlazada::Abin<T>::Nodo n) const;
};

template <typename T> const Abb<T> &Abb<T>::buscar(const T &e) const {
  if (raiz == nullptr) {
    return *this;
  } else if (e < raiz->elto) {
    return raiz->izq.buscar(e);
  } else if (raiz->elto < e) {
    return raiz->dch.buscar(e);
  } else {
    return *this;
  }
}

template <typename T> void Abb<T>::insertar(const T &e) {
  if (raiz == nullptr)
    raiz = new Nodo(e);
  else if (e < raiz->elto)
    raiz->izq.insertar(e);
  else if (raiz->elto < e)
    raiz->dch.insertar(e);
}

template <typename T> void Abb<T>::eliminar(const T &e) {
  if (raiz != nullptr) {
    if (e < raiz->elto) {
      raiz->izq.eliminar(e);
    } else if (raiz->elto < e) {
      raiz->dch.eliminar(e);
    } else if (raiz->izq.raiz == nullptr && raiz->dch.raiz == nullptr) {
      delete (raiz);
      raiz = nullptr;
    } else if (raiz->dch.raiz == nullptr) {
      Nodo *a{raiz->izq.raiz};
      raiz->izq.raiz = nullptr;
      delete (raiz);
      raiz = a;
    } else if (raiz->izq.raiz == nullptr) {
      Nodo *a{raiz->dch.raiz};
      raiz->dch.raiz = nullptr;
      delete (raiz);
      raiz = a;
    } else {
      raiz->elto = raiz->dch.borrarMin();
    }
  }
}

template <typename T> T Abb<T>::borrarMin() {
  if (raiz->izq.raiz == nullptr) {
    T e = raiz->elto;
    Nodo *hd{raiz->dch.raiz};
    raiz->dch.raiz = nullptr;
    delete (raiz);
    raiz = hd;
    return e;
  } else {
    return raiz->izq.borrarMin();
  }
}

template <typename T> inline const T &Abb<T>::elemento() const {
  assert(raiz != nullptr);
  return raiz->elto;
}

template <typename T> inline const Abb<T> &Abb<T>::izquierdo() const {
  assert(raiz != nullptr);
  return raiz->izq;
}

template <typename T> inline const Abb<T> &Abb<T>::derecho() const {
  assert(raiz != nullptr);
  return raiz->dch;
}

template <typename T> inline Abb<T>::Abb(const Abb<T> &a) : raiz{nullptr} {
  copiar(a);
}

template <typename T> Abb<T> &Abb<T>::operator=(const Abb<T> &a) {
  if (this != &a) {
    this->~Abb();
    copiar(a);
  }
  return *this;
}

template <typename T> Abb<T>::~Abb() {
  if (raiz != nullptr) {
    delete raiz;
    raiz = nullptr;
  }
}

template <typename T> void Abb<T>::copiar(const Abb<T> &a) {
  if (a.raiz != nullptr) {
    raiz = new Nodo(a.raiz->elto);
    raiz->izq.copiar(a.raiz->izq);
    raiz->dch.copiar(a.raiz->dch);
  }
}

template <typename T>
void Abb<T>::copiar(const Enlazada::Abin<T> &a,
                    typename Enlazada::Abin<T>::Nodo n) {
  if (n != Enlazada::Abin<T>::NODO_NULO) {
    insertar(a.elemento(n));
    copiar(a, a.hijoIzqdoB(n));
    copiar(a, a.hijoDrchoB(n));
  }
}

template <typename T>
void Abb<T>::copiarAbb(Enlazada::Abin<T> &abin,
                    typename Enlazada::Abin<T>::Nodo n) const {
  if (!raiz->izq.vacio()) {
    abin.insertarHijoIzqdoB(n, raiz->izq.elemento());
    raiz->izq.copiarAbb(abin, abin.hijoIzqdoB(n));
  }
  if (!raiz->dch.vacio()) {
    abin.insertarHijoDrchoB(n, raiz->dch.elemento());
    raiz->dch.copiarAbb(abin, abin.hijoDrchoB(n));
  }
}

template <typename T> void Abb<T>::podar(const T &e) {
  if (!vacio()) {
    if (e > raiz->elto) {
      raiz->dch.podar(e);
    } else if (e < raiz->elto) {
      raiz->izq.podar(e);
    } else {
      this->~Abb();
    }
  }
}

template <typename T> Abb<T>::operator Enlazada::Abin<T>() const {
  Enlazada::Abin<T> abin;
  if (!vacio()) {
    abin.insertarRaizB(elemento());
    copiarAbb(abin, abin.raizB());
  }
  return abin;
}
#endif