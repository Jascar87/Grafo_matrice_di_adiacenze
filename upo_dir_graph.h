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
 * @brief Restituisce il grado entrante di un vertice
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return il grado entrante di vertex, -1 se il grafo e' nullo
 */
int upo_get_in_degree(upo_dirgraph_t graph, int vertex);

/**
 * @brief Restituisce il grado uscente di un vertice
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return il grado uscente di vertex, -1 se il grafo e' nullo
 */
int upo_get_out_degree(upo_dirgraph_t graph, int vertex);

/**
 * @brief Restituisce il grado complessivo di un vertice
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return il grado complessivo di vertex, -1 se il grafo e' nullo
 */
int upo_get_degree(upo_dirgraph_t graph, int vertex);

/**
 * @brief Aggiunge un nuovo vertice al grafo di indice size+1 (dove size è il numero di vertici)
 *
 * @param graph il grafo
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_add_vertex(upo_dirgraph_t graph);

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
int upo_add_edge(upo_dirgraph_t graph, int vertex1, int vertex2);

/**
 * @brief Controlla l'esistenza di un arco nel grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se il grafo contiene l'arco, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_has_edge(upo_dirgraph_t graph, int vertex1, int vertex2);

/**
 * @brief Rimuove un arco dal grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_remove_edge(upo_dirgraph_t graph, int vertex1, int vertex2);

/**
 * @brief Controlla se due vertici sono adiacenti
 *
 * @param graph il grafo
 * @param vertex1 il primo vertice
 * @param vertex2 il secondo vertice
 * @return 1 se i vertici sono adiacenti, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_are_adj(upo_dirgraph_t graph, int vertex1, int vertex2);


/**
 * @brief Controlla se il grafo e' vuoto
 *
 * @param graph il grafo
 * @return 1 se il grafo e' vuoto, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_is_graph_empty(upo_dirgraph_t graph);

/**
 * @brief Restituisce una lista contenente i vertici adiacenti a vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente i vertici adiacenti a vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_get_adj_vert(upo_dirgraph_t graph, int vertex);

/**
 * @brief Restituisce una lista contenente gli archi uscenti da vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi uscenti da vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_get_inc_out_edg(upo_dirgraph_t graph, int vertex);

/**
 * @brief Restituisce una lista contenente gli archi entranti in vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi archi entranti in vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_get_inc_in_edg(upo_dirgraph_t graph, int vertex);

/**
 * @brief Restituisce una lista contenente gli archi incidenti a vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi incidenti a vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_get_inc_edg(upo_dirgraph_t graph, int vertex);

/**
 * @brief Restituisce una stringa rappresentante il grafo, nella forma Vertice: v;\n v -> i;\n v -> j\n dove i e j sono i vertici adiacenti a v
 *
 * @param graph il grafo
 * @return una stringa rappresentante il grafo
 */
char* upo_print_graph(upo_dirgraph_t graph);


#endif /* GRAPH_H */
