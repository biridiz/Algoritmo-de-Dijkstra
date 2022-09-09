/*
 * Algortimo de Dijkstra
 *
 * Autor: LUIZ ROBERTO DENDENA
 */

#include <stdio.h>
#include "grafo.h"

int main () {
    int numero_vertices;
    int numero_arestas;
    int numero_op;
    int vertice;
    int x, y, p;

    scanf("%d %d", &numero_vertices, &numero_arestas);
    
    Grafo *g = GRAFOconstroi(numero_vertices);

    for (int i=0; i<numero_arestas; i++) {
      scanf("%d %d %d", &x, &y, &p);
      Aresta aresta = ARESTA(x, y, p);
      GRAFOinsere_aresta(g, aresta);
    }

    scanf("%d", &numero_op);

    for (int i=0; i<numero_op; i++) {
      scanf("%d", &vertice);
      GRAFOimprime_distancias_caminhos(g, vertice);
    }

    GRAFOdestroi(g);

  return 0;
}
