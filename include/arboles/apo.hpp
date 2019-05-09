#ifndef APO_HPP
#define APO_HPP
#include <cassert>
template <typename T> class Apo {
public:
  Apo(int maxi) : max{maxi}, nodos{new T[max]}, ultimo{-1} {}

  Apo(const Apo<T> &a) : max{a.max}, nodos{new T[max]}, ultimo{a.ultimo} {
    for (Nodo = 0; n <= ultimo; ++n) {
      nodos[n] = a.nodos[n];
    }
  }

  Apo<T> &operator=(const Apo<T> &a) {
    if (this != &a) {
      if (max != a.max) {
        delete[] nodos;
        max = a.max;
        nodos = new T[max];
      }
      ultimo = a.ultimo;
      for (Nodo = 0; n <= ultimo; ++n) {
        nodos[n] = a.nodos[n];
      }
    }
    return *this;
  }

  void insertar(const T &e) {
    assert(ultimo < max - 1);
    nodos[++ultimo] = e;
    if (ultimo > 0) {
      flotar(ultimo);
    }
  }

  void suprimir() {
    assert(ultimo > -1) {
      if (--ultimo > -1) {
        nodos[0] = nodos[ultimo + 1];
        if (ultimo > 0) {
          hundir(0);
        }
      }
    }
  }

  const T &cima() const {
    assert(ultimo > -1);
    return nodos[0];
  }

  bool vacio() const { return ultimo == -1; }
  ~Apo() { delete[] nodos; }

private:
  using Nodo = int;
  int max;
  T *nodos;
  Nodo ultimo;
  Nodo padre(Nodo i) const { return (i - 1) / 2; }
  Nodo hizq(Nodo i) const { return 2 * i + 1; }
  Nodo hdch(Nodo i) const { return 2 * i + 2; }
  void flotar(Nodo i) {
    T e{nodos[i]};
    while (i > 0 && e < nodos[padre(i)]) {
      nodos[i] = nodos[padre(i)];
      i = padre(i);
    }
    nodos[i] = e;
  }
  void hundir(Nodo i) {
    bool fin = false;
    T e{nodos[i]};
    while (hizq(i) <= ultimo && !fin) {
      Nodo hmin;
      if (hizq(i) < ultimo && nodos[hdch(i)] < nodos[hizq(i)]) {
        hmin = hdch(i);
      } else {
        hmin = hizq(i);
        if (nodos[hmin] < e) {
          nodos[i] = nodos[hmin];
          i = hmin;
        } else {
          fin = true;
        }
      }
    }
    nodos[i] = e;
  }
};
#endif