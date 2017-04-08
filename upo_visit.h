
#ifndef UPO_VISIT_H
#define UPO_VISIT_H

#include "upo_dir_graph_adj_matrix.h"

/**
 * @brief Effettua una visita in ampiezza BFS semplice di un grafo graph a partire da un vertice sorgente source
 *
 * @param graph il grafo da visitare
 * @param source il vertice sorgente
 * @return il vettore dei padri dell'albero di visita, NULL se il grafo e' vuoto.
 *
 */
int* upo_BFS(upo_dirgraph_t graph, int source);

/**
 * @brief Effettua una visita in profondita' DFS totale ricorsiva di un grafo graph
 * Attenzione: per implementare questa funzione, sara' necessaria una funzione ausiliaria
 *
 * @param graph il grafo da visitare
 * @return il vettore dei padri della foresta di visita, NULL se il grafo e' vuoto.
 *
 */
int* upo_DFS_tot(upo_dirgraph_t graph);

/**
 * @brief Effettua una visita in profondita' DFS parziale ricorsiva di un grafo graph
 *
 * @param graph il grafo da visitare
 * @param vertex è il verice sorgente
 * @param color è il vettore che memorizza lo stato dei vettori
 * @param padri è il vettore che tiene l'ordina di visita
 * @param dim_visitati è il puntatore alla variabile che memorizza la dimensione dei vettori visitati
 * @return void
 *
 */

void upo_DFS_par(upo_dirgraph_t graph, int vertex, int* color, int* padri, int* dim_visitati);

/**
 * @brief Controlla se un grafo graph contiene dei cicli
 *
 * @param graph il grafo da esaminare
 * @return 1 se il grafo contiene cicli, 0 se e' aciclico, -1 se il grafo e' nullo
 *
 */
int upo_cyclic(upo_dirgraph_t graph);

/**
 * @brief controlla se esistono archi all' indietro 
 *
 * @param graph il grafo da esaminare
 * @param vertex è il vertice che stiamo considerando
 * @param color è il vettore che memorizza lo stato dei vettori
 * @return 1 se il grafo presenta un arco all'indietro se no 0
 *
 */

int upo_visit_ric_cyclic(upo_dirgraph_t graph,int vertex,int* color);

/**
 * @brief Controlla se un grafo graph e' un DAG (partendo dall'assunzione che sia diretto)
 *
 * @param graph il grafo da esaminare
 * @return 1 se il grafo e' un DAG, 0 se non lo e', -1 se il grafo e' nullo
 *
 */

int upo_is_DAG(upo_dirgraph_t graph);

/**
 * @brief Calcola un ordinamento topologico di un grafo graph
 *
 * @param graph il grafo da esaminare
 * @return il vettore ord dell'ordinamento topologico di graph
 *
 */
int* upo_topological_sort(upo_dirgraph_t graph);

/**
 * @brief Calcola le componenti fortemente connesse di un grafo graph con l'algoritmo di Kosaraju
 * Nota: per comodita', restituiamo la foresta delle cfc. Quando la stampate pero' fate capire che e' un multiinsieme e non una foresta
 *
 * @param graph il grafo da esaminare
 * @return la foresta delle componenti fortemente connesse restituita dall'algoritmo di Kosaraju
 *
 */
int* upo_strongly_connected_components(upo_dirgraph_t graph);

#endif /* UPO_VISIT_H */
