#ifndef GRAFO_H

#define GRAFO_H

#include "aresta.h"

typedef struct grafo Grafo;

typedef struct list {
    int item;
    int peso;
    struct list *next;
} List;

struct grafo {
    int num_vertices;
    int num_arestas;
    List **list;
};

Grafo *GRAFOconstroi(int num_vertices);

void GRAFOinsere_aresta(Grafo *g, Aresta e);

void GRAFOremove_aresta(Grafo *g, Aresta e);

void GRAFOarv_ger_pes_min(Grafo *g, int v, int *p, int *d);

void GRAFOimprime_distancias_caminhos(Grafo *g, int v);

void GRAFOimprime(Grafo *g);

void GRAFOdestroi(Grafo *g);

#endif /* GRAFO_H */
