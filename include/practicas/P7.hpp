#ifndef PRACTICAS_P7_HPP
#define PRACTICAS_P7_HPP

#include <algorithm>
#include <tuple>
#include "grafos/alg.hpp"

using grafos::Lista;
using grafos::matriz;
using grafos::pmc::GrafoP;
using grafos::pmc::alg::arista;
using grafos::pmc::alg::camino;
using grafos::pmc::alg::Dijkstra;
using grafos::pmc::alg::FloydMax;
using grafos::pmc::alg::tCamino;
using grafos::pmc::alg::vertice;
using std::size_t;

template <typename tCoste>
arista<tCoste> OtraVezUnGrafoSA(const GrafoP<tCoste>& G) {
  matriz<vertice<tCoste>> P;
  matriz<tCoste> F{FloydMax(G, P)};
  const size_t n = F.dimension();
  arista<tCoste> max_c(-1, -1, GrafoP<tCoste>::INFINITO * -1);
  for (vertice<tCoste> v = 0; v < n; ++v) {
    for (vertice<tCoste> w = 0; w < n; ++w) {
      if (F[v][w] > max_c.coste) {
        max_c = arista<tCoste>(v, w, F[v][w]);
      }
    }
  }
  return max_c;
}

template <typename tCoste>
std::tuple<tCoste, tCamino<tCoste>> Laberinto(
    size_t dim, const Lista<arista<tCoste>>& paredes, vertice<tCoste> inicio,
    vertice<tCoste> fin) {
  GrafoP<tCoste> L(dim * dim);
  for (vertice<tCoste> v = 0; v < dim * dim; ++v) {
    if (v < dim * (dim - 1)) {
      L[v][v + dim] = L[v + dim][v] = 1;
    }
    if (v % dim != dim - 1) {
      L[v][v + 1] = L[v + 1][v] = 1;
    }
  }
  for (auto it = paredes.primera(); it != paredes.fin();
       it = paredes.siguiente(it)) {
    const arista<tCoste>& p = paredes.elemento(it);
    L[p.orig][p.dest] = L[p.dest][p.orig] = GrafoP<tCoste>::INFINITO;
  }
  vector<vertice<tCoste>> P;
  vector<tCoste> D{Dijkstra(L, inicio, P)};
  return {D[fin], camino<tCoste>(inicio, fin, P)};
}

/**
 *
 * @todo Practica 7: Ejercicio 3
 * @body Finalizar la funcion de distribucion.
 */
template <typename tCoste>
void Distribucion(vertice<tCoste> centro, size_t cantidad,
                  const GrafoP<tCoste>& G, const vector<tCoste>& capacidad,
                  const vector<tCoste>& subvencion) {
  const size_t n{G.numVert()};
  matriz<tCoste> A(n);
  for (vertice<tCoste> v = 0; v < n; ++v) {
    A[v] = G[v];
    for (vertice<tCoste> w = 0; w < n; ++w) {
      if (A[v][w] != GrafoP<tCoste>::INFINITO) {
        A[v][w] *= cantidad;
      }
    }
  }
}

template <typename C>
double CementosZuelandia(const GrafoP<C>& G, vertice<C> capital,
                         const vector<C>& diario) {
  vector<vertice<C>> P;
  vector<C> D{Dijkstra(G, capital, P)};
  vector<C> Dinv{DijkstraInv(G, capital, P)};
  double km{0};
  D[capital] = Dinv[capital] = 0;
  for (vertice<C> v = 0; v < D.size(); ++v) {
    km += ((Dinv[v] + D[v]) * diario[v]);
  }
  return km;
}

/**
 *
 * @done Practica 7: Ejercicio 5
 *
 */
template <typename C>
vector<C> Alergico(const GrafoP<C>& carretera, const GrafoP<C>& tren,
                   const GrafoP<C>& avion, C presupuesto, vertice<C> alergico,
                   vertice<C> origen) {
  const size_t n{carretera.numVert()};
  vector<const GrafoP<C>*> grfs{&carretera, &tren, &avion};
  grfs.erase(grfs.begin() + alergico);
  GrafoP<C> min_transporte(n);
  const GrafoP<C> transporte0{*grfs[0]}, transporte1{*grfs[1]};
  for (vertice<C> v = 0; v < n; ++v) {
    for (vertice<C> w = 0; w < n; ++w) {
      min_transporte[v][w] = std::min(transporte0[v][w], transporte1[v][w]);
    }
  }
  vector<C> ciudades;
  vector<vertice<C>> P;
  vector<C> D{Dijkstra(min_transporte, origen, P)};
  for (size_t i = 0; i < n; ++i) {
    if (D[i] <= presupuesto && i != origen) {
      ciudades.push_back(i);
    }
  }
  return ciudades;
}

/**
 *
 * @todo Practica 7: Ejercicio 6
 * @body Al dueño de una agencia de transportes se le plantea la siguiente
 * situación. La agencia de viajes ofrece distintas trayectorias combinadas
 * entre N ciudades españolas utilizando tren y autobús. Se dispone de dos
 * grafos que representan los costes (matriz de costes) de viajar entre
 * diferentes ciudades, por un lado en tren, y por otro en autobús (por supuesto
 * entre las ciudades que tengan línea directa entre ellas). Además coincide que
 * los taxis de toda España se encuentran en estos momentos en huelga general,
 * lo que implica que sólo se podrá cambiar de transporte en una ciudad
 * determinada en la que, por casualidad, las estaciones de tren y autobús están
 * unidas. Implementa una función que calcule la tarifa mínima (matriz de costes
 * mínimos) de viajar entre cualesquiera de las N ciudades disponiendo del grafo
 * de costes en autobús, del grafo de costes en tren, y de la ciudad que tiene
 * las estaciones unidas.
 */

/**
 *
 * @todo Practica 7: Ejercicio 7
 * @body Se dispone de dos grafos (matriz de costes) que representan los costes
 * de viajar entre N ciudades españolas utilizando el tren (primer grafo) y el
 * autobús (segundo grafo). Ambos grafos representan viajes entre las mismas N
 * ciudades. Nuestro objetivo es hallar el camino de coste mínimo para viajar
 * entre dos ciudades concretas del grafo, origen y destino, en las siguientes
 * condiciones:
 * - La ciudad origen sólo dispone de transporte por tren.
 * - La ciudad destino sólo dispone de transporte por autobús.
 * - El sector del taxi, bastante conflictivo en nuestros problemas, sigue en
 * huelga, por lo que únicamente es posible cambiar de transporte en dos
 * ciudades del grafo, cambio1 y cambio2, donde las estaciones de tren y autobús
 * están unidas. Implementa un subprograma que calcule la ruta y el coste mínimo
 * para viajar entre las ciudades Origen y Destino en estas condiciones.
 */

/**
 *
 * @todo Practica 7: Ejercicio 8
 * @body "UN SOLO TRANSBORDO, POR FAVOR". Este es el título que reza en tu
 * flamante compañía de viajes. Tu publicidad explica, por supuesto, que ofreces
 * viajes combinados de TREN y/o AUTOBÚS (es decir, viajes en tren, en autobús,
 * o usando ambos), entre N ciudades del país, que ofreces un servicio
 * inmejorable, precios muy competitivos, y que garantizas ante notario algo que
 * no ofrece ninguno de tus competidores: que en todos tus viajes COMO MÁXIMO se
 * hará un solo transbordo (cambio de medio de transporte). Bien, hoy es 1 de
 * Julio y comienza la temporada de viajes. ¡Qué suerte! Acaba de aparecer un
 * cliente en tu oficina. Te explica que quiere viajar entre dos ciudades,
 * Origen y Destino, y quiere saber cuánto le costará. Para responder a esa
 * pregunta dispones de dos grafos de costes directos (matriz de costes) de
 * viajar entre las N ciudades del país, un grafo con los costes de viajar en
 * tren y otro en autobús. Implementa un subprograma que calcule la tarifa
 * mínima en estas condiciones. Mucha suerte en el negocio, que la competencia
 * es dura.
 */

/**
 *
 * @todo Practica 7: Ejercicio 9
 * @body Se dispone de dos grafos que representan la matriz de costes para
 * viajes en un determinado país, pero por diferentes medios de transporte (tren
 * y autobús, por ejemplo). Por supuesto ambos grafos tendrán el mismo número de
 * nodos, N. Dados ambos grafos, una ciudad de origen, una ciudad de destino y
 * el coste del taxi para cambiar de una estación a otra dentro de cualquier
 * ciudad (se supone constante e igual para todas las ciudades), implementa un
 * subprograma que calcule el camino y el coste mínimo para ir de la ciudad
 * origen a la ciudad destino.
 */

/**
 *
 * @todo Practica 7: Ejercicio 10
 * @body Se dispone de tres grafos que representan la matriz de costes para
 * viajes en un determinado país, pero por diferentes medios de transporte
 * (tren, autobús y avión). Por supuesto los tres grafos tendrán el mismo número
 * de nodos, N. Dados los siguientes datos:
 * - los tres grafos,
 * - una ciudad de origen,
 * - una ciudad de destino,
 * - el coste del taxi para cambiar, dentro de una ciudad, de la estación de
 * tren a la de autobús o viceversa (taxi-tren-bus) y
 * - el coste del taxi desde el aeropuerto a la estación de tren o la de
 * autobús, o viceversa (taxi-aeropuerto-tren/bus) y asumiendo que ambos costes
 * de taxi (distintos entre sí, son dos costes diferentes) son constantes e
 * iguales para todas las ciudades, implementa un subprograma que calcule el
 * camino y el coste mínimo para ir de la ciudad origen a la ciudad destino.
 */

/**
 *
 * @todo Practica 7: Ejercicio 11
 * @body Disponemos de tres grafos (matriz de costes) que representan los costes
 * directos de viajar entre las ciudades de tres de las islas del archipiélago
 * de las Huríes (Zuelandia). Para poder viajar de una isla a otra se dispone de
 * una serie de puentes que conectan ciudades de las diferentes islas a un
 * precio francamente asequible (por decisión del Prefecto de las Huríes, el uso
 * de los puentes es absolutamente gratuito). Si el alumno desea simplificar el
 * problema, puede numerar las N1 ciudades de la isla 1, del 0 al N1-1, las N2
 * ciudades de la isla 2, del N1 al N1+N2-1, y las N3 de la última, del N1+ N2
 * al N1+N2+ N3-1. Disponiendo de las tres matrices de costes directos de viajar
 * dentro de cada una de las islas, y la lista de puentes entre ciudades de las
 * mismas, calculad los costes mínimos de viajar entre cualesquiera dos ciudades
 * de estas tres islas.
 */

/**
 *
 * @todo Practica 7: Ejercicio 12
 * @body El archipiélago de Grecoland (Zuelandia) está formado únicamente por
 * dos islas, Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de
 * las cuales C1 y C2 ciudades son costeras (obviamente C1 ≤ N1 y C2 ≤ N2). Se
 * desea construir un puente que una ambas islas. Nuestro problema es elegir el
 * puente a construir entre todos los posibles, sabiendo que el coste de
 * construcción del puente se considera irrelevante. Por tanto, escogeremos
 * aquel puente que minimice el coste global de viajar entre todas las ciudades
 * de las dos islas, teniendo en cuenta las siguientes premisas:
 * - Se asume que el coste viajar entre las dos ciudades que una el puente es 0.
 * - Para poder plantearse las mejoras en el transporte que implica la
 * construcción de un puente frente a cualquier otro, se asume que se realizarán
 * exactamente el mismo número de viajes entre cualesquiera ciudades del
 * archipiélago. Por ejemplo, se considerará que el número de viajes entre la
 * ciudad P de Fobos y la Q de Deimos será el mismo que entre las ciudades R y S
 * de la misma isla. Dicho de otra forma, todos los posibles trayectos a
 * realizar dentro del archipiélago son igual de importantes. Dadas las matrices
 * de costes directos de Fobos y Deimos y las listas de ciudades costeras de
 * ambas islas, implementa un subprograma que calcule las dos ciudades que unirá
 * el puente.
 */

/**
 *
 * @todo Practica 7: Ejercicio 13
 * @body El archipiélago de las Huríes acaba de ser devastado por un maremoto de
 * dimensiones desconocidas hasta la fecha. La primera consecuencia ha sido que
 * todos y cada uno de los puentes que unían las diferentes ciudades de las tres
 * islas han sido destruidos. En misión de urgencia las Naciones Unidas han
 * decidido construir el mínimo número de puentes que permitan unir las tres
 * islas. Asumiendo que el coste de construcción de los puentes implicados los
 * pagará la ONU, por lo que se considera irrelevante, nuestro problema es
 * decidir qué puentes deben construirse. Las tres islas de las Huríes tienen
 * respectivamente N1, N2 y N3 ciudades, de las cuales C1, C2 y C3 son costeras
 * (obviamente C1 ≤ N1 , C2 ≤ N2 y C3 ≤ N3) . Nuestro problema es elegir los
 * puentes a construir entre todos los posibles. Por tanto, escogeremos aquellos
 * puentes que minimicen el coste global de viajar entre todas las ciudades de
 * las tres islas, teniendo en cuenta las siguientes premisas:
 * - Se asume que el coste viajar entre las ciudades que unan los puentes es 0.
 * - La ONU subvencionará únicamente el número mínimo de puentes necesario
 * para comunicar las tres islas.
 * - Para poder plantearse las mejoras en el transporte que implica la
 * construcción de un puente frente a cualquier otro, se asume que se realizarán
 * exactamente el mismo número de viajes entre cualesquiera ciudades del
 * archipélago. Dicho de otra forma, todos los posibles trayectos a realizar
 * dentro del archipiélago son igual de importantes. Dadas las matrices de
 * costes directos de las tres islas y las listas de ciudades costeras del
 * archipiélago, implementad un subprograma que calcule los puentes a construir
 * en las condiciones anteriormente descritas.
 */
#endif