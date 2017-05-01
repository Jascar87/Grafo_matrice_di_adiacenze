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
     int vertex=-1;
     int scoperti=0;
     upo_list_t adj_list=NULL;
     queue = upo_create_list(sizeof(int),NULL);
     for(i=0; i<graph->n; i++) color[i]= WHITE;/**ciclo che inizializza a WHITE gli elementi di color*/
     color[source]=GREY;/**source diventa GREY*/
     upo_add_last(queue, &source);/**inserisco in coda source*/
     scoperti++;
     padri=realloc(padri, sizeof(int)*scoperti);
     assert(padri!=NULL);
     padri[scoperti-1]=source;

     while(upo_list_size(queue)>0){
       for(i=0; i<graph->n;i++) printf("vert %d color %d\n",i,color[i]);//debug
       printf("\n");//debug
       adj_list=upo_get_adj_vert(graph, *((int*)upo_get_first(queue)));
       printf("vert %d adj_list_size %d\n\n", *((int*)upo_get_first(queue)), upo_list_size(adj_list));//debug
       while (upo_list_size(adj_list)>0){/**scorro tutta la lista di adiacienza del nodo analizzato*/
         vertex=*((int*)upo_remove_first(adj_list));
         if (color[vertex]==WHITE){/**se il colore del vertice considerato e' WHITE*/
           color[vertex]=GREY;/**coloro il vertice di GREY*/
           int *newTail = malloc(sizeof(int));
           *newTail = vertex;
           upo_add_last(queue, &(*newTail));/**inserisco il vertice in coda*/
            printf("\t\tnew tail %d\n", *((int*)upo_get_last(queue)));
           scoperti++;
           padri=realloc(padri, sizeof(int)*scoperti);
           assert(padri!=NULL);
           padri[scoperti-1]=vertex;
         }
       }

       color[*((int*)upo_get_first(queue))] = BLACK;/**finito il ciclo rimuovo l'elemento considerato dalla coda e lo coloro di BLACK*/

       free(upo_remove_first(queue));
     }

     padri=realloc(padri, sizeof(int)*(scoperti+1));
     assert(padri!=NULL);
     padri[scoperti]=-1;
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
  int last_free = graph->n -1;/**variabile che tiene traccia dell'ultima posizione libera di last_free*/
  int end = 0;
  int *padri=NULL;/**puntatore per il vettore dei padri*/
  int vertex_visitati=0;
  int vett_elemento_corrente[graph->n];
  for (i=0; i<graph->n; i++) color[i]=WHITE;/**ciclo che inizializza a WHITE gli elementi di color e adj_vector  a NULL*/

  while(end==0){
    printf("vertex %d\n", vertex);
    printf("TOT vertex_visitati = %d\n", vertex_visitati);
    padri=realloc(padri, (sizeof(int)*(vertex_visitati+1)));/**alloco lo spazio per un nuovo elemento del vettore dei padri*/
    assert(padri!=NULL);
    padri[vertex_visitati] = vertex;
    printf("padri di indice %d e' %d\n", vertex_visitati, padri[vertex_visitati]);
    upo_DFS_par(graph, vertex, color, padri, &vertex_visitati, NULL);
    color[vertex]=BLACK;
    for(i=vertex; i<graph->n && color[i]!=WHITE; i++);/** cicla fino a trovare il primo nodo WHITE*/
    if (i==graph->n) end=1; /**controllo se ho terminato il ciclo perchè ho scoperto tutti i nodi*/
    else if (color[i]==WHITE) vertex = i;/** imposto vertex al nuvo nodo WHITE individuato*/
    printf("\t\t vertex: %d\n", vertex);
  }

  for(i=0; i<graph->n; i++) printf("vert %d color %d\n",i,color[i]);
  for(i=0; i<graph->n; i++) printf("elemento %d = %d\n", i+1, padri[i]);//debug
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
 * @param f è la lista che tiene traccia del ordine di chiusura dei nodi, l'ordine e'decrescente (viene gestita la lista se e solo se f è una lista "creata")
 * @return void
 *
 */

void upo_DFS_par(upo_dirgraph_t graph, int vertex, int* color, int* padri, int* vertex_visitati, upo_list_t f){
  int* vertex_corrente=NULL;
  upo_list_t adj_list=NULL;
  if(upo_is_graph_empty(graph)!=0) return;/**controllo che esista e non sia vuoto il grafo*/
  if (((*vertex_visitati)+1)==graph->n) return;/**caso di terminazione ho visitato tutti i nodi*/
  adj_list = upo_create_list(sizeof(int),NULL);
  printf("vertex: %d\n", vertex);
  color[vertex]=GREY;
  printf("color di indice %d e' %d\n", vertex, color[vertex]);
  (*vertex_visitati)++;
/**
 * visita di vertex
 */
  adj_list=upo_get_adj_vert(graph, vertex);
  while(upo_list_size(adj_list)>0){
    vertex_corrente=upo_get_first(adj_list);
    if (color[(*vertex_corrente)]==WHITE){
      printf("vertex_corrente %d\n", *vertex_corrente);
        printf("\tPAR vertex_visitati = %d\n", *vertex_visitati);
      padri=realloc(padri, sizeof(int)*((*vertex_visitati)+1));/**alloco lo spazio per un nuovo elemento del vettore dei padri*/
      assert(padri!=NULL);
      padri[*vertex_visitati] = (*vertex_corrente);
      printf("padri di indice %d e' %d\n", *vertex_visitati, padri[*vertex_visitati]);
      upo_DFS_par(graph, *vertex_corrente, color, padri, vertex_visitati, f);
    }
    upo_remove_first(adj_list);
  }
  upo_destroy_list(adj_list);
  color[vertex]=BLACK;
  printf("color di indice %d e' %d\n", vertex, color[vertex]);
  if(f!=NULL) upo_add_first(f, &vertex);
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
  return FALSE;
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
  int* vertex_pointer=NULL;
  upo_list_t adj_list=upo_get_adj_vert(graph, vertex);
  adj_list=upo_create_list(sizeof(int),NULL);
  while(upo_list_size(adj_list)>0){
    vertex_pointer=upo_remove_first(adj_list);
    if (color[(*vertex_pointer)]==WHITE){
      if (upo_visit_ric_cyclic(graph, (*vertex_pointer), color)==TRUE){
        upo_destroy_list(adj_list);
        return TRUE;
      }
    }
    else if (color[(*vertex_pointer)]==WHITE){
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
  int color[graph->n];/**vettore per identificare i colori dei nodi*/
  int d[graph->n]; /**vettore per tenere traccia del tempo di scoperta del nodo i-esimo*/
  upo_list_t f;/**lista per tenere traccia dell'ordine di chiusura dei nodi*/
  int vertex = 0; /**variabile che tiene il vertice che si stà considerando*/
  int i;
  int vett_elemento_corrente[graph->n];
  int end = 0;
  int *ord_topologico=NULL;/**puntatore per il vettore da restituire*/
  int temp[graph->n]; /**vettore per invertire l'ordine di ord_topologico*/
  int vertex_visitati=0;
  f=upo_create_list(sizeof(int),NULL);
  for (i=0; i<graph->n; i++){/**ciclo che inizializza a WHITE gli elementi di color e vett_elemento_corrente  a NULL*/
    color[graph->n]=WHITE;
    vett_elemento_corrente[i]=i;
  }
  do{
    upo_DFS_par(graph, vett_elemento_corrente[vertex], color, ord_topologico, &vertex_visitati, f);
    for(i=vertex; i<graph->n || color[i]!=WHITE; i++);/** cicla fino a trovare il primo nodo WHITE*/
    if (i==graph->n) end=1; /**controllo se ho terminato il ciclo perchè ho scoperto tutti i nodi*/
    else if (color[i]==WHITE) vertex = i;/** imposto vertex al nuvo nodo WHITE*/
  }
  while(end==0);
  for (i=0; i<graph->n; i++) temp[graph->n-(i+1)]= ord_topologico[i]; /**copio in ordine invertito in temp*/
  for (i=0; i<graph->n; i++) ord_topologico[i]= temp[i]; /** copio ordinatamente in ord_topologico*/
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
    vector_strongly_connected = NULL;
    int color[graph->n];/**vettore per identificare i colori dei nodi*/
    upo_list_t f;/**lista per tenere traccia dei tempi di chiusura dei nodi */
    int vertex = 0; /**variabile che tiene il vertice che si stà considerando*/
    int vett_elemento_corrente[graph->n];
    int i, j;
    int last_free = graph->n -1;
    int end = 0;
    int temp[graph->n]; /** vettore */
    int vertex_visitati=0;
    upo_dirgraph_t trasposto = NULL;
    for (i=0; i<graph->n; i++){/**ciclo che inizializza a WHITE gli elementi di color e vett_elemento_corrente*/
      color[graph->n]=WHITE;
      vett_elemento_corrente[i]=i;
    }

    do{
      upo_DFS_par(graph, vett_elemento_corrente[vertex], color, temp, &vertex_visitati, f);
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
  int j=0;
  if(upo_is_graph_empty(sorgente)!=FALSE)  return -1;
  trasposto=upo_dirgraph_create(sorgente->n);
  for (i=0; i<sorgente->n; i++) upo_add_vertex(trasposto);
  for (i=0; i<sorgente->n; i++){
    for(j=0; j<sorgente->n; j++){
      if (sorgente->adj[i][j]==1)trasposto->adj[j][i]=1;/**se esiste l'arco in sorgente[i][j] allora lo creo in trasposto[j][i]*/
    }
  }
  return 1;
}
