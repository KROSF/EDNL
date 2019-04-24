#ifndef ABB_HPP
#define ABB_HPP
#include <cassert>
template <typename T> class Abb {
public:
  Abb() : raiz{nullptr} {}
  Abb(const Abb &a) : raiz{nullptr} { copiar(a); }
  void insertar(const T &);
  void eliminar(const T &);
  bool vacio() { return raiz == nullptr; }
  const T &elemento() const {
    assert(raiz != nullptr);
    return raiz->elto;
  }
  const Abb &izquierdo() const {
    assert(raiz != nullptr);
    return raiz->izq;
  }
  const Abb &derecho() const {
    assert(raiz != nullptr);
    return raiz->dch;
  }
  Abb &operator=(const Abb &a) {
    if (this != &a) {
      this->~Abb();
      copiar(a);
    }
    return *this;
  }
  ~Abb() {
    if (raiz != nullptr) {
      delete raiz;
      raiz = nullptr;
    }
  }

private:
  class Nodo {
  public:
    T elto;
    Abb izq, dch;
  };
  Nodo *raiz;
  const Abb &buscar(const T &e) const;
  T borrarMin();
  void copiar(const Abb<T> &a);
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

template <typename T> void Abb<T>::copiar(const Abb<T> &a) {
  if (a.raiz != 0) {
    raiz = new Nodo(a.raiz->elto);
    raiz->izq.copiar(a.raiz->izq);
    raiz->dch.copiar(a.raiz->dch);
  }
}

template <typename T> void Abb<T>::insertar(const T &e) {
  if (raiz == nullptr) {
    raiz->elto = e;
  } else if (e < elto) {
    raiz->izq.insertar(e);
  } else if (e > elto) {
    raiz->dch.insertar(e);
  }
}

template <typename T> void Abb<T>::eliminar(const T &e) {
  if (raiz != nullptr) {
    if (e < raiz->elto) {
      raiz->izq.eliminar(e);
    } else if (raiz->elto < e) {
      raiz->dch.eliminar(e);
    } else {
      if (raiz->izq.raiz == nullptr && raiz->dch.raiz == nullptr) {
        delete raiz;
        raiz == nullptr;
      } else if (raiz->dch.raiz == 0) {
        Nodo *a{raiz->izq.raiz};
        raiz->izq.raiz = 0;
        delete (raiz);
        raiz = a;
      } else if (raiz->izq.raiz == 0) {
        Nodo *a{raiz->dch.raiz};
        raiz->dch.raiz = 0;
        delete (raiz);
        raiz = a;
      } else {
        raiz->elto = raiz->dch.borrarMin();
      }
    }
  }
}

#endif