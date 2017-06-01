#include "upo_visit.h"
#include "upo_dir_graph_adj_matrix.c"
#include "upo_list.c"
#include <assert.h>
#define WHITE 0
#define GREY 1
#define BLACK 2
#define TRUE 1
#define FALSE 0

/**
 * @brief Effettua una visita in ampiezza BFS semplice di un grafo graph a partire da un vertice sorgente source
 *
 * @param graph il grafo da visitare
 * @param source il vertice sorgente
 * @return il vettore dei padri dell'albero di visita, NULL se il grafo e' vuoto.
 *
 */
 int* upo_BFS(upo_dirgraph_t graph, int source) {
     if(upo_is_graph_empty(graph)!=0) return NULL;/**controllo che esista e non sia vuoto il grafo*/
     int color[graph->n];/**vettore per identificare i colori dei nodi*/
     upo_list_t queue = NULL;
     int *padri=NULL;/**puntatore per il vettore dei padri*/
     int i;
     int *vertex=NULL;
     int *vertex_corrente=NULL;
     int scoperti=0;
     int vett_elemento_corrente[graph->n];/**vettore che associa alla cella i-esima il numero i-esimo*/
     upo_list_t adj_list=NULL;
     padri=malloc(sizeof(int)*(graph->n));
     assert(padri!=NULL);
     queue = upo_create_list(sizeof(int),NULL);
     for(i=0; i<graph->n; i++) {/**ciclo che inizializza a WHITE gli elementi di color e il vetore dei padri a -1 e il vettore degli elementi correnti*/
       color[i]= WHITE;
       padri[i]=-1;
       vett_elemento_corrente[i]=i;
     }
     color[source]=GREY;/**source diventa GREY*/
     upo_add_last(queue, &source);/**inserisco in coda source*/
     while(upo_list_size(queue)>0){
       vertex=upo_get_first(queue);
       adj_list=upo_get_adj_vert(graph, *vertex);
       while (upo_list_size(adj_list)>0){/**scorro tutta la lista di adiacienza del nodo analizzato*/
         vertex_corrente=upo_get_first(adj_list);
         if (color[*vertex_corrente]==WHITE){/**se il colore del vertice considerato e' WHITE*/
           color[*vertex_corrente]=GREY;/**coloro il vertice di GREY*/
           upo_add_last(queue, &vett_elemento_corrente[*vertex_corrente]);/**inserisco la copia del valore puntato da vertex_corrente in coda*/
           padri[*vertex_corrente] = *vertex;
         }
         upo_remove_first(adj_list);
       }
       color[*vertex] = BLACK;/**finito il ciclo l'elemento considerato lo coloro di BLACK*/
       upo_remove_first(queue);
    }
     upo_destroy_list(adj_list);
     upo_destroy_list(queue);
     return padri;/**restiruisco i padri*/
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
  if(upo_is_graph_empty(graph)!=0) return NULL;/**controllo che esista e non sia vuoto il grafo*/
  int color[graph->n];/**vettore per identificare i colori dei nodi*/
  int vertex = 0; /**variabile che tiene il vertice che si stà considerando*/
  int i;
  int end = 0;
  int* padri=NULL;/**puntatore al vettore dei padri*/
  int vertex_visitati=0;
  int vett_elemento_corrente[graph->n];
  padri=malloc(sizeof(int)*(graph->n));
  assert(padri!=NULL);
  for (i=0; i<graph->n; i++){ /**ciclo che inizializza a WHITE gli elementi di color e il vettore dei padri*/
    color[i]=WHITE;
    padri[i]=-1;
  }
  for(i=0; i<graph->n; i++){
    if(color[i]==WHITE) upo_DFS_par(graph, i, color, padri, &vertex_visitati, NULL, NULL);
  }

  return padri;

}

/**
 * @brief Effettua una visita in profondita' DFS parziale ricorsiva di un grafo graph
 *
 * @param graph il grafo da visitare
 * @param vertex e' il puntatore del vertice sorgente
 * @param color e' il vettore che memorizza lo stato dei vettori
 * @param padri e' il vettore che tiene l'ordina di visita
 * @param vertex_visitati è il puntatore alla variabile che memorizza la dimensione dei vettori visitati
 * @param fine_visita è la lista che memorizza i vertici in ordine decrescentedi chiusura
 * @param vett_elemento_corrente è il puntatore al vettore che ha il valore i-esimo nella cella i-esima
 * @return void
 *
 */

void upo_DFS_par(upo_dirgraph_t graph, int vertex, int* color, int* padri, int* vertex_visitati, upo_list_t fine_visita, int* vett_elemento_corrente){
  int* vertex_corrente=NULL;
  upo_list_t adj_list=NULL;
  if(upo_is_graph_empty(graph)!=0) return;/**controllo che esista e non sia vuoto il grafo*/
  if (((*vertex_visitati)+1)==graph->n) return;/**caso di terminazione ho visitato tutti i nodi*/
  color[vertex]=GREY;
  (*vertex_visitati)++;
/**
 * visita di vertex
 */
  adj_list=upo_get_adj_vert(graph, vertex);
  while(upo_list_size(adj_list)>0){
    vertex_corrente=upo_get_first(adj_list);
    if (color[(*vertex_corrente)]==WHITE){
      padri[*vertex_corrente] = vertex;
      upo_DFS_par(graph, *vertex_corrente, color, padri, vertex_visitati, fine_visita, vett_elemento_corrente);
    }
    upo_remove_first(adj_list);
  }
  upo_destroy_list(adj_list);
  color[vertex]=BLACK;
  if(fine_visita!=NULL) upo_add_first(fine_visita, &vett_elemento_corrente[vertex]);
}

/**
 * @brief Controlla se un grafo graph contiene dei cicli
 *
 * @param graph il grafo da esaminare
 * @return 1 se il grafo contiene cicli, 0 se e' aciclico, -1 se il grafo e' nullo
 *
 */
int upo_cyclic(upo_dirgraph_t graph) {
  if (graph==NULL) return -1;
  int i = 0;
  int predecessori[graph->n];
  int color[graph->n];/**vettore per identificare i colori dei nodi*/
  int vertex = 0; /**variabile che tiene il vertice che si stà considerando*/
  for(i = 0; i<graph->n; i++){
    color[i]=WHITE;
    predecessori[1]=-1;
  }
  for(vertex = 0; vertex<graph->n; vertex++) {
    if (color[vertex]==WHITE && (upo_visit_ric_cyclic(graph, vertex, color, predecessori)==TRUE)) return TRUE;
  }
   return FALSE;
}

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

int upo_visit_ric_cyclic(upo_dirgraph_t graph, int vertex, int* color, int* predecessori){
  color[vertex]=GREY;
  int i;
  int* vertex_corrente=NULL;
  upo_list_t adj_list=upo_create_list(sizeof(int),NULL);
  adj_list=upo_get_adj_vert(graph, vertex);
  while(upo_list_size(adj_list)>0){
    vertex_corrente=upo_remove_first(adj_list);
    if (color[(*vertex_corrente)]==WHITE){
      predecessori[*vertex_corrente]=vertex;
      if (upo_visit_ric_cyclic(graph, *vertex_corrente, color, predecessori)==TRUE){
        upo_destroy_list(adj_list);
        return TRUE;
      }
    }
    else if (color[*vertex_corrente]==GREY){
      upo_destroy_list(adj_list);
      return TRUE;
    }
  }
  color[vertex]=BLACK;
  upo_destroy_list(adj_list);
  return FALSE;
}

/**
 * @brief Controlla se un grafo graph e' un DAG (partendo dall'assunzione che sia diretto)
 *
 * @param graph il grafo da esaminare
 * @return 1 se il grafo e' un DAG, 0 se non lo e', -1 se il grafo e' nullo
 *
 */
 int upo_is_DAG(upo_dirgraph_t graph) {
     if (graph==NULL) return -1;
     if (upo_cyclic(graph) == FALSE) return TRUE; /**se il grafo non ha cicli allora è un DAG*/
     else return FALSE;
 }

/**
 * @brief Calcola un ordinamento topologico di un grafo graph
 *
 * @param graph il grafo da esaminare
 * @return il vettore ord dell'ordinamento topologico di graph
 *
 */

int* upo_topological_sort(upo_dirgraph_t graph) {
  int *ord_topologico=NULL;/**puntatore per il vettore da restituire*/
  if(graph==NULL) return NULL;
  if(upo_is_DAG(graph)==FALSE) return NULL; /**se il grafo non è un DAG restituisco NULL*/
  int color[graph->n];/**vettore per identificare i colori dei nodi*/
  int vertex = 0; /**variabile che tiene il vertice che si stà considerando*/
  int i;
  int end = 0;
  int timer=0;
  int last_free=graph->n-1;
  int padri[graph->n];/**vettore dei padri*/
  int d[graph->n]; /**vettor che memorizza il tempo di scoperta del nodo i-esimo nella cella i-esima*/
  int f[graph->n]; /**vettor che memorizza il tempo di chiusura del nodo i-esimo nella cella i-esima*/
  int vett_elemento_corrente[graph->n];
  ord_topologico=malloc(sizeof(int)*(graph->n));
  assert(ord_topologico!=NULL);
  for (i=0; i<graph->n; i++){ /**ciclo che inizializza a WHITE gli elementi di color e il vettore dei padri*/
    color[i]=WHITE;
    ord_topologico[i]=-1;
    padri[i]=-1;
    f[i]=-1;
    d[i]=-1;
  }
  for(i=0; i<graph->n; i++){
    if(color[i]==WHITE) upo_DFS_topological(graph, i, ord_topologico, padri, color, &last_free, &timer, d, f);
  }
  return ord_topologico;
}

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

void upo_DFS_topological(upo_dirgraph_t graph, int vertex, int* ord_topologico,int* padri, int*color, int* last_free, int* timer, int* d, int* f){
  int* vertex_corrente=NULL;
  upo_list_t adj_list=NULL;
  adj_list = upo_create_list(sizeof(int),NULL);
  color[vertex]=GREY;
  d[vertex]= ++(*timer);
  adj_list=upo_get_adj_vert(graph, vertex);
  while(upo_list_size(adj_list)>0){
    vertex_corrente=upo_get_first(adj_list);
    if (color[(*vertex_corrente)]==WHITE){
      padri[*vertex_corrente] = vertex;
      upo_DFS_topological(graph, *vertex_corrente, ord_topologico, padri, color, last_free, timer, d, f);
    }
    upo_remove_first(adj_list);
  }
  upo_destroy_list(adj_list);
  color[vertex]=BLACK;
  f[vertex]= ++(*timer);
  ord_topologico[(*last_free)--]=vertex;
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
    if (upo_is_graph_empty(graph)!= 0) return NULL;/**return NULL se il grafo è vuoto o non ha vertici*/
    int* vector_strongly_connected = NULL; /**vettore che indicherà in che componente fortemente connessa si trova il vertice i-esimo*/
    vector_strongly_connected = malloc(sizeof(int)*(graph->n));
    assert(vector_strongly_connected!=NULL);
    int color[graph->n];/**vettore per identificare i colori dei nodi*/
    upo_list_t fine_visita;/**lista per tenere traccia dei tempi di chiusura dei nodi */
    int* vertex = 0; /**variabile che tiene il vertice che si stà considerando*/
    int i;
    int vett_elemento_corrente[graph->n];
    int padri[graph->n];
    int end = 0;
    int vertex_visitati=0;
    fine_visita=upo_create_list(sizeof(int), NULL);
    upo_dirgraph_t trasposto = NULL;
    for (i=0; i<graph->n; i++){ /**ciclo che inizializza a WHITE gli elementi di color e il vettore dei padri*/
      color[i]=WHITE;
      padri[i]=-1;
      vett_elemento_corrente[i]=i;
      vector_strongly_connected[i]=-1;
    }
    for(i=0; i<graph->n; i++){/**alla fine del ciclo fine_visita conterrà tutti i vertici in ordine decrescente di fine visita*/
      if(color[i]==WHITE) upo_DFS_par(graph, i, color, vector_strongly_connected, &vertex_visitati, fine_visita, vett_elemento_corrente);
    }
    upo_dirgraph_trasposto(graph, &trasposto);
    for (i=0; i<graph->n; i++) color[i]=WHITE; /**ciclo che inizializza a WHITE gli elementi di color*/

    while(upo_list_size(fine_visita)>0){
      vertex=upo_remove_first(fine_visita);
      if (color[*vertex]==WHITE) upo_DFS_par(trasposto, i, color, vector_strongly_connected, &vertex_visitati, NULL, NULL);
    }
    upo_destroy_list(fine_visita);
    upo_dirgraph_destroy(trasposto);
    for(i=0; i<graph->n; i++)
    return vector_strongly_connected;
}

/**
 * @brief Crea un grafo trasposto
 *
 * @param sorgente è il grafo da cui  si crea il grafo trasposto
 * @param trasposto è il puntatore in cui restituire il grafo traspoto creato
 * @return -1  se il grafo è vuoto o non esiste, 1 se il grafo e' stato creato correttamente
 *
 */
int upo_dirgraph_trasposto (upo_dirgraph_t sorgente, upo_dirgraph_t *trasposto){
  int i=0;
  int j=0;
  if(upo_is_graph_empty(sorgente)!=FALSE)  return -1;
  *trasposto=upo_dirgraph_create(sorgente->n);
  for (i=0; i<sorgente->n; i++) upo_add_vertex(*trasposto);
  for (i=0; i<sorgente->n; i++){
    for(j=0; j<sorgente->n; j++){
      if (sorgente->adj[i][j]==1)(*trasposto)->adj[j][i]=1;/**se esiste l'arco in sorgente->adj[i][j] allora lo creo in trasposto->adj[j][i]*/
    }
  }
  return 1;
}
