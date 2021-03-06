
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
 * @param vertex e' il puntatore del vertice sorgente
 * @param color e' il vettore che memorizza lo stato dei vettori
 * @param padri e' il vettore che tiene l'ordina di visita
 * @param fine_visita è la lista che memorizza i vertici in ordine decrescentedi chiusura (puo' essere NULL)
 * @param vett_elemento_corrente è il puntatore al vettore che ha il valore i-esimo nella cella i-esima (puo' essere NULL)
 * @return void
 *
 */

void upo_DFS_par(upo_dirgraph_t graph, int vertex, int* color, int* padri, upo_list_t fine_visita, int* vett_elemento_corrente);

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
 * @param predecessori è il vettore che memorizza i predecessori
 * @return 1 se il grafo presenta un arco all'indietro se no 0
 *
 */

int upo_visit_ric_cyclic(upo_dirgraph_t graph, int vertex, int* color, int* predecessori);

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
 * @brief Calcola ricorsivamente l'ordine topologico
 *
 * @param graph il grafo da esaminare
 * @param vertex è il vertice che stiamo considerando
 * @param ord_topologico è il vettore che memorizza l'ordine topologico
 * @param predecessori è il vettore che memorizza i predecessori
 * @param color è il vettore che memorizza lo stato dei vettori
 * @param last_free è il puntatore alla variabile che memorizza l'ultima cella libera di ord_topologico
 * @param timer è il puntatore alla variabile che memorizza il tempo
 * @param d è il puntatore al vettore che tiene traccia del tempo di scoperta dei nodi
 * @param f è il puntatore al vettore che tiene traccia del tempo di chiusura dei nodi
 * @return
 *
 */

void upo_DFS_topological(upo_dirgraph_t graph, int vertex, int* ord_topologico,int* padri, int*color, int* last_free, int* timer, int* d, int* f);

/**
 * @brief Calcola le componenti fortemente connesse di un grafo graph con l'algoritmo di Kosaraju
 * Nota: per comodita', restituiamo la foresta delle cfc. Quando la stampate pero' fate capire che e' un multiinsieme e non una foresta
 *
 * @param graph il grafo da esaminare
 * @return la foresta delle componenti fortemente connesse restituita dall'algoritmo di Kosaraju
 *
 */

int* upo_strongly_connected_components(upo_dirgraph_t graph);

/**
 * @brief Crea un grafo trasposto
 *
 * @param sorgente è il grafo da cui  si crea il grafo traspost
 * @param trasposto è il puntatore in cui restituire il grafo traspoto creato
 * @return -1  se il grafo è vuoto o non esiste, 1 se il grafo e' stato creato correttamente
 *
 */
int upo_dirgraph_trasposto (upo_dirgraph_t sorgente, upo_dirgraph_t* trasposto);
#endif /* UPO_VISIT_H */
