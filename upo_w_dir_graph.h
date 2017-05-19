#include <string.h>
#include "upo_list.h"

#ifndef UPO_DIR_GRAPH_H
#define UPO_DIR_GRAPH_H

typedef struct upo_dirgraph_s* upo_dirgraph_t;
typedef struct upo_dir_edge_s* upo_dir_edge_t;

/**
 * @brief Definizione della struttura per rappresentare un arco diretto
 */
typedef struct upo_dir_edge_s {
    int from; /**< Vertice da cui l'arco esce. */
    int to; /**< Vertice nel quale l'arco entra. */
} upo_dir_edge_s;

/**
 * @brief Crea un nuovo grafo orientato
 *
 * @param n dimensione della matrice di adiacenza da creare
 * @return un nuovo grafo diretto vuoto
 *
 */
upo_dirgraph_t upo_dirgraph_create(int n);

/**
 * @brief Distrugge un grafo liberando tutta la memoria
 *
 * @param graph il grafo da eliminare
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_dirgraph_destroy(upo_dirgraph_t graph);

/**
 * @brief Restituisce il numero di vertici del grafo
 *
 * @param graph il grafo
 * @return il numero di vertici del grafo, -1 se il grafo e' nullo
 */
int upo_num_vertices(upo_dirgraph_t graph);

/**
 * @brief Restituisce il numero di archi del grafo
 *
 * @param graph il grafo
 * @return il numero di archi del grafo, -1 se il grafo e' nullo
 */
int upo_num_edges(upo_dirgraph_t graph);

/**
 * @brief Aggiunge un nuovo vertice al grafo di indice size+1 (dove size è il numero di vertici)
 *
 * @param graph il grafo
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_w_add_vertex(upo_dirgraph_t graph);

/**
 * @brief Controlla l'esistenza di un vertice di indice vertex nel grafo
 *
 * @param graph il grafo
 * @param vertex il vertice da cercare
 * @return 1 se il grafo contiene il vertice, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_has_vertex(upo_dirgraph_t graph, int vertex);

/**
 * @brief Elimina un vertice di indice vertex dal grafo e tutti gli archi ad esso incidenti. Attenzione, le liste di adiacenza vanno aggiornate.
 *
 * @param graph il grafo
 * @param vertex il vertice da eliminare
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_remove_vertex(upo_dirgraph_t graph, int vertex);

/**
 * @brief Aggiunge un arco al grafo. Se l'arco gia' esiste non fa nulla
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_add_edge(upo_dirgraph_t graph, int vertex1, int vertex2);

/**
 * @brief Controlla l'esistenza di un arco nel grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se il grafo contiene l'arco, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_has_edge(upo_dirgraph_t graph, int vertex1, int vertex2);

/**
 * @brief Restituisce il peso di un'arco
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_has_weight_edge(upo_dirgraph_t graph, int vertex1, int vertex2);

/**
 * @brief Rimuove un arco dal grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */


int upo_w_remove_edge(upo_dirgraph_t graph, int vertex1, int vertex2);

/**
 * @brief Controlla se il grafo e' vuoto
 *
 * @param graph il grafo
 * @return 1 se il grafo e' vuoto, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_is_graph_empty(upo_dirgraph_t graph);

/**
 * @brief Restituisce una stringa rappresentante il grafo, nella forma Vertice: v;\n v -> i;\n v -> j\n dove i e j sono i vertici adiacenti a v
 *
 * @param graph il grafo
 * @return una stringa rappresentante il grafo
 */
char* upo_print_graph(upo_dirgraph_t graph);

/**
 * @brief alloca e valorizza il vettore delle distane e dei padri per una ricerca dei cammini minimi a partire da una sorgente
 *
 * @param graph e' il grafo pesato
 * @param source e' la sorgenta da cui calcolare i cammini minimi
 * @param p_padri e' il puntatore al vettore dei padri
 * @param p_distanze e' il puntatore al vettore delle distanze
 * @return 1 se l'operazione e' andata a buon fine, restituisce un valore negativo in caso contrario
 */
int upo_cmDijkstra(upo_wdirgraph_t graph, int source, int* p_padri, int* p_distanze);

/**
 * @brief cerca il valroe minimo nella coda di priorita' e restituisce la sua posizione
 *
 * @param graph e' il grafo pesato
 * @param priority e' il puntatore al vettore della coda di priorita'
 * @return -1 se non si trovano altri elementi in coda o restituisce la posizione con priorita' maggiore(valore minore)
 */
int upo_get_min(int* priority);


#endif /* GRAPH_H */
