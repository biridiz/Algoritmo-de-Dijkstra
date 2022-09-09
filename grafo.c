#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "aresta.h"
#include "heap.h"

#define INT_MAX 999999999


Grafo *GRAFOconstroi (int num_vertices) {
    Grafo *g = malloc(sizeof(*g));
    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    g->list = malloc(num_vertices * sizeof(*g->list));

    for (int i = 0; i < num_vertices; i++) {
        g->list[i] = NULL;
    }

    return g;
}

int GRAFOverifica_aresta (Grafo *g, Aresta e) {
    List *aux = g->list[e.v1];

    while (aux != NULL) {
        if (aux->item == e.v2) {
            return 1;
        }
        aux = aux->next;
    }

    return 0;
}

void GRAFOinsere_aresta(Grafo *g, Aresta e) {
    if (e.v1 == e.v2) return;
    if (GRAFOverifica_aresta(g, e)) return;

    List *aux = malloc(sizeof(List));
    
    aux->item = e.v2;
    aux->peso = e.peso;
    aux->next = g->list[e.v1];
    g->list[e.v1] = aux;
    
    g->num_arestas++;
}

void GRAFOremove_aresta(Grafo *g, Aresta e) {
    if (!GRAFOverifica_aresta(g, e)) return;

    List *aux = g->list[e.v1];
    List *ant = NULL;

    while (aux != NULL && aux->item != e.v2) {
        ant = aux;
        aux = aux->next;
    }

    if (aux != NULL) {
        if (ant == NULL) {
            g->list[e.v1] = aux->next;
        } else {
            ant->next = aux->next;
        }
    }

    g->num_arestas--;
}

int *GRAFOinicializa_vetor_caminhos(Grafo *g) {
    int *vetorCaminhos = malloc(g->num_vertices * sizeof(*vetorCaminhos));
    for (int i = 0; i < g->num_vertices; i++) {
        vetorCaminhos[i] = -1;
    }
    return vetorCaminhos;
}

int *GRAFOinicializa_vetor_distancia(Grafo *g) {
    int *vetorDistancia = malloc(g->num_vertices * sizeof(*vetorDistancia));
    for (int i = 0; i < g->num_vertices; i++) {
        vetorDistancia[i] = INT_MAX;
    }
    return vetorDistancia;
}

void GRAFOcaminho(int i, int pai[]) {
    if (pai[i] == -1) {
        printf("%d", i);

    } else {
        printf("%d ", i);
        GRAFOcaminho(pai[i], pai);
    }
}

void GRAFOarv_ger_pes_min(Grafo *g, int v, int *pai, int *dist)  {
    Heap *heap = HEAPconstroi(g->num_vertices);
  
    for (int i=0; i<g->num_vertices; i++) {
        ElementoHeap item;
        item.vertice = i;
        item.peso = INT_MAX;
        HEAPinsere(heap, item);
    }
  
    dist[v] = 0;
    HEAPaltera_peso(heap, v, 0);

    while (!HEAPvazia(heap)) {
        ElementoHeap min = HEAPremove(heap);
        int w = min.vertice;

        if (dist[w] != INT_MAX) {
            List *wu = g->list[w];
            while (wu != NULL) {
                if (HEAPtem_vertice(heap, wu->item)) {
                    ElementoHeap u = HEAPbusca(heap, wu->item);
                    
                    if (dist[u.vertice] > (dist[w] + wu->peso)) {
                        dist[u.vertice] = dist[w] + wu->peso;
                        HEAPaltera_peso(heap, u.vertice, wu->peso);
                        pai[u.vertice] = w;
                    }
                }
                wu = wu->next;
            }
        }
    }
}

void GRAFOimprime_distancias_caminhos (Grafo *g, int v) {
    int *pai = GRAFOinicializa_vetor_caminhos(g);
    int *dist = GRAFOinicializa_vetor_distancia(g);

    GRAFOarv_ger_pes_min(g, v, pai, dist);

    for (int i = 0; i < g->num_vertices; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d: infinita, sem caminho partindo de %d\n", i, v);

        } else {
            printf("%d: %d, ", i, dist[i]);
            GRAFOcaminho(i, pai);
            printf("\n");
        }
    }
    printf("\n");
}

void GRAFOimprime(Grafo *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        List *aux = g->list[i];
        printf("%d:", i);
        while (aux != NULL) {
            printf(" %d ", aux->item);
            aux = aux->next;
        }
        printf("\n");
    }
}

void GRAFOdestroi(Grafo *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        while (g->list[i] != NULL) {
            List *aux = g->list[i];
            g->list[i] = g->list[i]->next;
            free(aux);
        }
    }
    free(g->list);
    free(g);
}