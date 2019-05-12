#ifndef APO_HPP
#define APO_HPP
namespace grafos {
#include <cassert>
template <typename T>
// Arbol Parcialmente Ordenado
class Apo {
 public:
  // Construye un Arbol Parcialmente Ordenado.
  explicit Apo(std::size_t max_n)
      : max{static_cast<int>(max_n)}, nodos{new T[max]}, ultimo{-1} {}
  // Crea una copia de un Arbol Parcialmente Ordenado.
  Apo(const Apo& a) : max{a.max}, nodos{new T[max]}, ultimo{a.ultimo} {
    for (nodo n = 0; n <= ultimo; n++) nodos[n] = a.nodos[n];
  }
  Apo& operator=(const Apo&);
  // Inserta un elemento en el arbol.
  void insertar(const T& e);
  // Elimina elemento en la raiz del arbol.
  void suprimir();
  // Devuelve el elemento de la raiz del arbol.
  const T& cima() const;
  // Comprueba si el arbol esta vacio.
  bool vacio() const { return ultimo == -1; }
  // Destruye el Arbol
  ~Apo() { delete[] nodos; }

 private:
  using nodo = int;
  // Numero Maximo de elementos que puede contener el arbol.
  int max;
  // Nodos que componen el arbol.
  T* nodos;
  // Posicion del ultimo nodo insertado.
  nodo ultimo;
  // Flota un elemento hacia la cima.
  void flotar(nodo);
  // Hunde un elemento hacia el fondo.
  void hundir(nodo);
  // Devuelve la posicion del padre de un nodo.
  nodo padre(nodo n) const { return (n - 1) / 2; }
  // Devuelve el hijo izquierdo de un nodo.
  nodo hIzq(nodo n) const { return 2 * n + 1; }
  // Devuelve el hijo derecho de un nodo.
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
