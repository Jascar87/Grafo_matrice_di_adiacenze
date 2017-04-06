#include "upo_visit.h"
#include <assert.h>
#define WHITE 0
#define GREY 1
#define BLACK 2

/**
 * @brief Effettua una visita in ampiezza BFS semplice di un grafo graph a partire da un vertice sorgente source
 *
 * @param graph il grafo da visitare
 * @param source il vertice sorgente
 * @return il vettore dei padri dell'albero di visita, NULL se il grafo e' vuoto.
 *
 */
int* upo_BFS(upo_dirgraph_t graph, int source) {
    if(upo_is_graph_empty(graph)!=0) return NULL;//controllo che esista e non sia vuoto il grafo
    int color[graph->n];//vettore per identificare i colori dei nodi
    int queue[(graph->n)+1];//vettore per gestire la coda
    int head_queue = 0;//contatore alla testa della coda
    int tail_queue = 0; //contatore alla fine della coda
    int *padri=NULL;//puntatore per il vettore dei padri
    int i;
    queue[(graph->n)+1]=-1;//limite massimo della coda
    upo_list_t edge = NULL; //puntatore alla lista degli archi
    upo_list_t edge_copy = NULL;
    for(i=0; i<graph->n; i++);{//ciclo che inizializza a WHITE i nodi in color e queue  a -1
      color[i]= WHITE;
      queue[i]=-1;
    }
    color[source]=GREY;//source diventa GREY
    queue[tail_queue++]=source;//inserisco in coda source e incremento tail_quee
    edge=upo_get_inc_out_edg(source);
    edge_copy=edge;
    while(queue[head_quee]!=-1){
      edge=upo_get_inc_out_edg(queue[head_queue]);//creo la lista degli archi uscenti dal vertice in testa alla coda
      edge_copy=edge;
      while (edge!=NULL){
        if (color[edge->upo_dir_edge_s->to]==WHITE){//se il colore del vertice puntato WHITE
          color[edge->upo_dir_edge_s->to]=GREY;//coloro il vertice di GREY
          quee[tail_queue++]=edge->upo_dir_edge_s->to;//inserisco il vertice in coda e incremento la fine coda
        }
        edge=edge->next;
        color[queue[head_queue++]] = BLACK;//coloro di BLACK il nodo in testa alla coda e faccio avanzare la coda
      }
      upo_destroy_list(edge_copy);
    }
    padri=malloc(sizeof(int)*(tail_queue+1));
    assert(padri!=NULL);
    for(i=0; i<tail_queue; i++) padri[i]=queue[i];//copio i valori da queue a padri
    return padri;//restiruisco i padri
}

/**
 * @brief Effettua una visita in profondita' DFS totale ricorsiva di un grafo graph
 * Attenzione: per implementare questa funzione, sara' necessaria una funzione ausiliaria
 *
 * @param graph il grafo da visitare
 * @return il vettore dei padri della foresta di visita, NULL se il grafo e' vuoto.
 *
 */
int* upo_DFS_tot(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Controlla se un grafo graph contiene dei cicli
 *
 * @param graph il grafo da esaminare
 * @return 1 se il grafo contiene cicli, 0 se e' aciclico, -1 se il grafo e' nullo
 *
 */
int upo_cyclic(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Controlla se un grafo graph e' un DAG (partendo dall'assunzione che sia diretto)
 *
 * @param graph il grafo da esaminare
 * @return 1 se il grafo e' un DAG, 0 se non lo e', -1 se il grafo e' nullo
 *
 */
int upo_is_DAG(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Calcola un ordinamento topologico di un grafo graph
 *
 * @param graph il grafo da esaminare
 * @return il vettore ord dell'ordinamento topologico di graph
 *
 */
int* upo_topological_sort(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Calcola le componenti fortemente connesse di un grafo graph con l'algoritmo di Kosaraju
 * Nota: per comodita', restituiamo la foresta delle cfc. Quando la stampate pero' fate capire che e' un multiinsieme e non una foresta
 *
 * @param graph il grafo da esaminare
 * @return la foresta delle componenti fortemente connesse restituita dall'algoritmo di Kosaraju
 *
 */
int* upo_strongly_connected_components(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
}
