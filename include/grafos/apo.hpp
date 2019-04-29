#ifndef APO_HPP
#define APO_HPP
namespace grafos {
#include <cassert>
template <typename T>
class Apo {
 public:
  explicit Apo(size_t max_n) : max{max_n}, nodos{new T[max]}, ultimo{-1} {}
  Apo(const Apo& a) : max{a.max}, nodos{new T[max]}, ultimo{a.ultimo} {
    for (nodo n = 0; n <= ultimo; n++) nodos[n] = a.nodos[n];
  }
  Apo& operator=(const Apo&);
  void insertar(const T& e);
  void suprimir();
  const T& cima() const;
  bool vacio() const { return ultimo == -1; }
  ~Apo() { delete[] nodos; }

 private:
  using nodo = int;
  int max;
  T* nodos;
  nodo ultimo;
  void flotar(nodo);
  void hundir(nodo);
  nodo padre(nodo n) const { return (n - 1) / 2; }
  nodo hIzq(nodo n) const { return 2 * n + 1; }
  nodo hDer(nodo n) const { return 2 * n + 2; }
};

template <typename T>
inline void Apo<T>::insertar(const T& e) {
  assert(ultimo < max - 1);
  nodos[++ultimo] = e;
  flotar(ultimo);
}

template <typename T>
inline void Apo<T>::suprimir() {
  assert(ultimo > -1);
  if (--ultimo > -1) {
    nodos[0] = nodos[ultimo + 1];
    if (ultimo > 0) hundir(0);
  }
}

template <typename T>
inline const T& Apo<T>::cima() const {
  assert(ultimo > -1);
  return nodos[0];
}

template <typename T>
Apo<T>& Apo<T>::operator=(const Apo<T>& a) {
  if (this != &a) {
    if (max != a.max) {
      delete[] nodos;
      max = a.max;
      nodos = new T[max];
    }
    ultimo = a.ultimo;
    for (nodo n = 0; n <= ultimo; n++) nodos[n] = a.nodos[n];
  }
  return *this;
}

template <typename T>
void Apo<T>::flotar(nodo i) {
  T e = nodos[i];
  while (i > 0 && e < nodos[padre(i)]) {
    nodos[i] = nodos[padre(i)];
    i = padre(i);
  }
  nodos[i] = e;
}

template <typename T>
void Apo<T>::hundir(nodo i) {
  bool fin = false;
  T e = nodos[i];
  while (hIzq(i) <= ultimo && !fin) {
    nodo hMin;
    if (hIzq(i) < ultimo && nodos[hDer(i)] < nodos[hIzq(i)]) {
      hMin = hDer(i);
    } else {
      hMin = hIzq(i);
    }
    if (nodos[hMin] < e) {
      nodos[i] = nodos[hMin];
      i = hMin;
    } else {
      fin = true;
    }
  }
  nodos[i] = e;
}
}  // namespace grafos
#endif
