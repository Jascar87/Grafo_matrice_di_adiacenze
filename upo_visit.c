#include "upo_visit.h"
#include "upo_dir_graph_adj_matrix.c"
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
    int queue[(graph->n)+1];/**vettore per gestire la coda*/
    int head_queue = 0;/**contatore alla testa della coda*/
    int tail_queue = 0; /**contatore alla fine della coda*/
    int *padri=NULL;/**puntatore per il vettore dei padri*/
    int i;
    queue[(graph->n)+1]=-1;/**limite massimo della coda*/
    upo_list_t edge = NULL; /**puntatore alla lista degli archi*/
    upo_list_node* edge_copy = NULL;
    for(i=0; i<graph->n; i++);{/**ciclo che inizializza a WHITE gli elementi di color e queue  a -1*/
      color[i]= WHITE;
      queue[i]=-1;
    }
    color[source]=GREY;/**source diventa GREY*/
    queue[tail_queue++]=source;/**inserisco in coda source e incremento tail_quee*/
    while(queue[head_quee]!=-1){
      edge=upo_get_inc_out_edg(graph, queue[head_queue]);/**creo la lista degli archi uscenti dal vertice in testa alla coda*/
      edge_copy=edge->head;
      while (edge!=NULL){
        if (color[edge_copy->element->to]==WHITE){/**se il colore del vertice puntato WHITE*/
          color[edge_copy->element->to]=GREY;/**coloro il vertice di GREY*/
          quee[tail_queue++]=edge_copy->element->to;/**inserisco il vertice in coda e incremento la fine coda*/
        }
        edge_copy=edge_copy->next;
        color[queue[head_queue++]] = BLACK;/**coloro di BLACK il nodo in testa alla coda e faccio avanzare la coda*/
      }
      upo_destroy_list(edge);
    }
    padri=malloc(sizeof(int)*(tail_queue+1));
    assert(padri!=NULL);
    for(i=0; i<tail_queue; i++) padri[i]=queue[i];/**copio i valori da queue a padri*/
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
  int f[graph->n];/**vettore che tiene traccia del ordine di chiusura dei nodi, l'ordine e'decrescente*/
  int vertex = 0; /**variabile che tiene il vertice che si stà considerando*/
  int i;
  int last_free = graph->n -1;/**variabile che tiene traccia dell'ultima posizione libera di last_free*/
  int end = 0;
  int *padri=malloc(graph->n*sizeof(int));/**puntatore per il vettore dei padri*/
  int vertex_visitati=0;
  for (i=0; i<graph->n; i++){/**ciclo che inizializza a WHITE gli elementi di color e adj_vector  a NULL*/
    color[graph->n]=WHITE;
    f[i]=-1;
  }
  do{
    upo_DFS_par(graph, vertex, color, padri, &vertex_visitati, &last_free, f);
    for(i=vertex; i<graph->n || color[i]!=WHITE; i++);/** cicla fino a trovare il primo nodo WHITE*/
    if (i==graph->n) end=1; /**controllo se ho terminato il ciclo perchè ho scoperto tutti i nodi*/
    else if (color[i]==WHITE) vertex = i;/** imposto vertex al nuvo nodo WHITE*/
  }
  while(end==0);
  return padri;

}

/**
 * @brief Effettua una visita in profondita' DFS parziale ricorsiva di un grafo graph
 *
 * @param graph il grafo da visitare
 * @param vertex e' il verice sorgente
 * @param color e' il vettore che memorizza lo stato dei vettori
 * @param padri e' il vettore che tiene l'ordina di visita
 * @param vertex_visitati è il puntatore alla variabile che memorizza la dimensione dei vettori visitati
 * @param last_free tiene traccia dell'ultima posizione vuota di f[]
 * @param f è il puntatore al vettore che tiene traccia del ordine di chiusura dei nodi, l'ordine e'decrescente
 * @return void
 *
 */

void upo_DFS_par(upo_dirgraph_t graph, int vertex, int* color, int* padri, int* vertex_visitati, int* last_free, int* f){
  if(upo_is_graph_empty(graph)!=0) return ;/**controllo che esista e non sia vuoto il grafo*/
  if (((*vertex_visitati)+1)==graph->n);/**caso di terminazione ho visitato tutti i nodi*/
  upo_list_node* adj_list_copy=adj_list->head;
  color[vertex]=GREY;
  padri[((*vertex_visitati)++)]=vertex;
  upo_list_t adj_list=upo_get_adj_vert(graph, vertex);
  while (adj_list!=NULL) {
    if (adj_list_copy->element!=NULL){
      if (color[adj_list_copy->element]==WHITE) timer = upo_DFS_par(graph, adj_list_copy->element, color, padri, vertex_visitati, last_free, f);
    }
  }
  upo_destroy_list(adj_list);
  color[vertex]=BLACK;
  f[(*last_free)--] = vertex;
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
  int color[graph->n];/**vettore per identificare i colori dei nodi*/
  int vertex = 0; /**variabile che tiene il vertice che si stà considerando*/
  for(i = 0; i<graph->n; i++){
    color[i]=GREY;
  }
  for(vertex = 0; vertex<graph->n; vertex++){
    if (color[vertex]==WHITE && upo_visit_ric_cyclic(graph, vertex, color)) return TRUE;
  }
  else return FALSE;
}

/**
 * @brief controlla se esistono archi all' indietro
 *
 * @param graph il grafo da esaminare
 * @param vertex è il vertice che stiamo considerando
 * @param color è il vettore che memorizza lo stato dei vettori
 * @return 1 se il grafo presenta un arco all'indietro se no 0
 *
 */

int upo_visit_ric_cyclic(upo_dirgraph_t graph,int vertex,int* color){
  color[vertex]=GREY;
  int i;
  upo_list_node* adj_list_copy=NULL;
  upo_list_t adj_list=upo_get_adj_vert(graph, vertex);
  adj_list_copy=adj_list->head;
  for (i=0; i<adj_list->logicalLength; i++){
    if (color[adj_list_copy->element]==WHITE){
      if (upo_visit_ric_cyclic(graph, adj_list_copy->element)){
        /** non capisco lo pseudocodice Pgreca[v]<-u */
        upo_destroy_list(adj_list);
        return TRUE;
      }
    }
    else if (color[adj_list_copy->element]==WHITE){
      upo_destroy_list(adj_list);
      return TRUE;
    }
    adj_list_copy=adj_list_copy->next;
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
  int color[graph->n];/**vettore per identificare i colori dei nodi*/
  int d[graph->n]; /**vettore per tenere traccia del tempo di scoperta del nodo i-esimo*/
  int f[graph->n];/**vettore per tenere traccia del tempo di chiusura del nodo i-esimo*/
  int vertex = 0; /**variabile che tiene il vertice che si stà considerando*/
  int i;
  int last_free = graph->n -1;
  int end = 0;
  int *ord_topologico=malloc(graph->n*sizeof(int));/**puntatore per il vettore da restituire*/
  int temp[graph->n]; /** vettore per invertire l'ordine di ord_topologico*/
  int vertex_visitati=0;
  for (i=0; i<graph->n; i++){/**ciclo che inizializza a WHITE gli elementi di color e adj_vector  a NULL*/
    color[graph->n]=WHITE;
    d[i]=-1;
    f[i]=-1;
  }
  do{
    upo_DFS_par(graph, vertex, color, ord_topologico, &vertex_visitati, &last_free, f);
    for(i=vertex; i<graph->n || color[i]!=WHITE; i++);/** cicla fino a trovare il primo nodo WHITE*/
    if (i==graph->n) end=1; /**controllo se ho terminato il ciclo perchè ho scoperto tutti i nodi*/
    else if (color[i]==WHITE) vertex = i;/** imposto vertex al nuvo nodo WHITE*/
  }
  while(end==0);
  for (i=0; ì<graph->n; i++) temp[graph->n-(i+1)]= ord_topologico[i]; /**copio in ordine invertito in temp*/
  for (i=0; ì<graph->n; i++) ord_topologico[i]= temp[i]; /** copio ordinatamente in ord_topologico*/
  return ord_topologico;
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
    if (upo_is_graph_empty(graph)!=FALSE) return NULL;/**return NULL se il grafo è vuoto o non ha vertici*/
    int* vector_strongly_connected = NULL; /**vettore che indicherà in che componente fortemente connessa si trova il vertice i-esimo*/
    vector_strongly_connected = malloc(sizeof(int)*graph->n);
    int color[graph->n];/**vettore per identificare i colori dei nodi*/
    int d[graph->n]; /**vettore per tenere traccia del tempo di scoperta del nodo i-esimo*/
    int f[graph->n];/**vettore per tenere traccia del tempo di chiusura del nodo i-esimo*/
    int vertex = 0; /**variabile che tiene il vertice che si stà considerando*/
    int i, j;
    int last_free = graph->n -1;
    int end = 0;
    int temp[graph->n]; /** vettore */
    int vertex_visitati=0;
    upo_dirgraph_t trasposto = NULL;
    for (i=0; i<graph->n; i++){/**ciclo che inizializza a WHITE gli elementi di color e adj_vector  a NULL*/
      color[graph->n]=WHITE;
      f[i]=-1;
    }

    do{
      upo_DFS_par(graph, vertex, color, temp, &vertex_visitati, last_free, f);
      for(i=vertex; i<graph->n || color[i]!=WHITE; i++);/** cicla fino a trovare il primo nodo WHITE*/
      if (i==graph->n) end=1; /**controllo se ho terminato il ciclo perchè ho scoperto tutti i nodi*/
      else if (color[i]==WHITE) vertex = i;/** imposto vertex al nuvo nodo WHITE*/
    }
    while(end==0);
    upo_dirgraph_trasposto(graph, trasposto);




    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Crea un grafo trasposto
 *
 * @param sorgente è il grafo da cui  si crea il grafo traspost
 * @param trasposto è il puntatore in cui restituire il grafo traspoto creato
 * @return -1  se il grafo è vuoto o non esiste, 1 se il grafo e' stato creato correttamente
 *
 */
int upo_dirgraph_trasposto (upo_dirgraph_t sorgente, upo_dirgraph_t trasposto){
  int i=0;
  if(upo_is_graph_empty(graph)!=FALSE)  return -1;
  trasposto=upo_dirgraph_create(sorgente->n);
  for (i=0; i<sorgente->n; i++) upo_add_vertex(trasposto);
  for (i=0; i<sorgente->n; i++){
    for(j=0; j<sorgente->n; j++){
      if (sorgente->adj[i][j]==1)trasposto->adj[j][i]=1;/**se esiste l'arco in sorgente[i][j] allora lo creo in trasposto[j][i]*/
    }
  }
  return 1;
}
