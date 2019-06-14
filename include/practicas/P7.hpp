#ifndef PRACTICAS_P7_HPP
#define PRACTICAS_P7_HPP

#include "grafos/alg.hpp"

using grafos::Lista;
using grafos::matriz;
using grafos::pmc::GrafoP;
using grafos::pmc::alg::arista;
using grafos::pmc::alg::BigGrafo;
using grafos::pmc::alg::camino;
using grafos::pmc::alg::caminoInv;
using grafos::pmc::alg::Dijkstra;
using grafos::pmc::alg::FloydMax;
using grafos::pmc::alg::min_with_index;
using grafos::pmc::alg::tCamino;
using grafos::pmc::alg::vertice;
using std::size_t;

/**
 * @done Practica 7: Ejercicio 1
 */
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

/**
 * @done Practica 7: Ejercicio 2
 */
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
 * @done Practica 7: Ejercicio 3
 * @body Finalizar la funcion de distribucion.
 */
template <typename tCoste>
std::tuple<vector<tCoste>, tCoste> Distribucion(
    const GrafoP<tCoste>& ciudades, const vertice<tCoste>& centro_prod,
    tCoste cantidad, const vector<tCoste>& capacidad,
    const vector<tCoste>& subv) {
  size_t n = subv.size();
  vector<tCoste> cants_ciud(n, 0);
  vector<double> subvenciones(subv.begin(), subv.end());
  tCoste coste = 0;

  vector<vertice<tCoste>> P;
  vector<tCoste> D = Dijkstra(ciudades, centro_prod, P);

  for (vertice<tCoste> i = 0; i < n && cantidad > 0; ++i) {
    auto it = max_element(subvenciones.begin(), subvenciones.end());
    int ind = distance(subvenciones.begin(), it);
    if (capacidad[ind] <= cantidad) {
      cants_ciud[ind] = capacidad[ind];
      coste += D[ind] - (tCoste)((*it) * D[ind] / 100);
      cantidad -= capacidad[ind];
      subvenciones[ind] = 0;
    }
  }
  return {cants_ciud, coste};
}

/**
 * @done Practica 7: Ejercicio 4
 */
template <typename C>
double CementosZuelandia(const GrafoP<C>& G, vertice<C> capital,
                         const vector<C>& diario) {
  vector<vertice<C>> P;
  vector<C> D{Dijkstra(G, capital, P)};
  vector<C> Dinv{DijkstraInv(G, capital, P)};
  double km{0};
  for (vertice<C> v = 0; v < D.size(); ++v) {
    km += ((Dinv[v] + D[v]) * diario[v]);
  }
  return km;
}

/**
 * @done Practica 7: Ejercicio 5
 */
template <typename C>
vector<C> Alergico(const GrafoP<C>& carretera, const GrafoP<C>& tren,
                   const GrafoP<C>& avion, C presupuesto, vertice<C> alergico,
                   vertice<C> origen) {
  const size_t n{carretera.numVert()};
  vector<const GrafoP<C>*> grfs{&carretera, &avion, &tren};
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
 * @done Practica 7: Ejercicio 6
 */
template <typename C>
matriz<C> AgenciaTransporteSinTaxi(const GrafoP<C>& bus, const GrafoP<C>& tren,
                                   vertice<C> estacion) {
  matriz<vertice<C>> P;
  matriz<C> F_Bus{Floyd(bus, P)};
  matriz<C> F_Tren{Floyd(tren, P)};
  const size_t dim{bus.numVert()};
  matriz<C> F_min(dim);
  for (vertice<C> v = 0; v < dim; ++v) {
    for (vertice<C> w = 0; w < dim; ++w) {
      F_min[v][w] = std::min({F_Bus[v][w], F_Tren[v][w],
                              F_Bus[v][estacion] + F_Tren[estacion][w],
                              F_Tren[v][estacion] + F_Tren[estacion][w]});
    }
  }
  return F_min;
}

/**
 * @done Practica 7: Ejercicio 7
 */
template <typename C>
std::tuple<C, tCamino<C>> TransporteSinTaxiDosEstaciones(
    const GrafoP<C>& tren, const GrafoP<C>& bus, vertice<C> origen,
    vertice<C> destino, vertice<C> estacion, vertice<C> estacion2) {
  vector<vertice<C>> Porig, Pdest;
  vector<C> D{Dijkstra(tren, origen, Porig)};
  vector<C> Dinv{DijkstraInv(bus, destino, Pdest)};
  tCamino<C> path;
  C min_coste{D[estacion] + Dinv[estacion]},
      coste_e2{D[estacion2] + Dinv[estacion2]};
  if (min_coste < coste_e2) {
    path = camino<C>(origen, estacion, Porig);
    path.eliminar(path.anterior(path.fin()));
    path += caminoInv<C>(destino, estacion, Pdest);
  } else {
    min_coste = coste_e2;
    path = camino<C>(origen, estacion2, Porig);
    path.eliminar(path.anterior(path.fin()));
    path += caminoInv<C>(destino, estacion2, Pdest);
  }
  return {min_coste, path};
}

/**
 * @done Practica 7: Ejercicio 8
 */
template <typename C>
C UnSoloTransbordo(const GrafoP<C>& tren, const GrafoP<C>& bus,
                   vertice<C> origen, vertice<C> destino) {
  vector<vertice<C>> P;
  vector<C> DTren{Dijkstra(tren, origen, P)};
  vector<C> DInvTren{DijkstraInv(tren, destino, P)};
  vector<C> DBus{Dijkstra(bus, origen, P)};
  vector<C> DInvBus{DijkstraInv(bus, destino, P)};
  const size_t n = tren.numVert();
  vector<C> min_elem(2 * n);
  for (size_t i = 0; i < n; ++i) {
    min_elem[i] = DTren[i] + DInvBus[i];
    min_elem[n + i] = DBus[i] + DInvTren[i];
  }
  return *std::min_element(min_elem.begin(), min_elem.end());
}

/**
 * @done Practica 7: Ejercicio 9
 */
template <typename C>
std::tuple<C, tCamino<C>> TransporteConTaxi(const GrafoP<C>& bus,
                                            const GrafoP<C>& tren,
                                            vertice<C> origen,
                                            vertice<C> destino) {
  const size_t n = bus.numVert();
  GrafoP<C> BG{BigGrafo<C>({tren, bus}, 1)};
  vector<vertice<C>> P;
  vector<C> D{Dijkstra(BG, origen, P)};
  tCamino<C> path;
  if (D[destino] < D[destino + n]) {
    path = camino<C>(origen, destino, P);
  } else {
    path = camino<C>(origen, destino + n, P);
  }
  for (auto it = path.primera(); it != path.fin(); it = path.siguiente(it)) {
    if (path.elemento(it) > n - 1) {
      path.elemento(it) -= n;
    }
  }
  return {std::min(D[destino], D[destino + n]), path};
}

/**
 * @done Practica 7: Ejercicio 10
 */
template <typename C>
std::tuple<C, tCamino<C>> TransporteConTaxi2(
    const GrafoP<C>& tren, const GrafoP<C>& bus, const GrafoP<C>& avion,
    vertice<C> origen, vertice<C> destino, C t_b, C a_t_b) {
  const size_t n = tren.numVert();
  vector<C> v_t_b(n, t_b);
  vector<C> v_a_t_b(n, a_t_b);
  GrafoP<C> BG{BigGrafo<C>({tren, bus, avion}, {v_t_b, v_a_t_b, v_a_t_b})};
  vector<vertice<C>> P;
  vector<C> D{Dijkstra(BG, origen, P)};
  tCamino<C> path;
  auto [index, value] =
      min_with_index<C>({D[destino], D[destino + n], D[destino + 2 * n]});
  path = camino<C>(origen, destino + index * n, P);
  for (auto it = path.primera(); it != path.fin(); it = path.siguiente(it)) {
    if (path.elemento(it) > 2 * n - 1) path.elemento(it) -= 2 * n;
    if (path.elemento(it) > n - 1) path.elemento(it) -= n;
  }
  return {value, path};
}
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