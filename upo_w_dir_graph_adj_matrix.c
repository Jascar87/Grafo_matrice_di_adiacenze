#include "upo_w_dir_graph_adj_matrix.h"
#include <assert.h>
#include <limits.h>
#define DIM_STRING 1024
#define DIM_BUF 20



/**
 * @brief Crea un nuovo grafo orientato
 *
 * @param n dimensione della matrice di adiacenza da creare
 * @return un nuovo grafo diretto vuoto
 *
 */

upo_w_dirgraph_t upo_w_dirgraph_create(int n) {
    upo_w_dirgraph_t graph = NULL;
    graph = malloc(sizeof(upo_w_dirgraph_s)); /**< Allocazione della struttura grafo e controllo con assert. */
    assert(graph!=NULL);
    graph->n = 0;
    if(n < 1){ /**< Controllo che n abbia un valore valido. */
      n = 1;
    }
    graph->adj=NULL;
    graph->adj = malloc(sizeof(int**[n])); /**< Creazione della matrice di adiacenza e controllo con assert. */
    assert(graph->adj!=NULL);
    int row = 0;
    int column = 0;
    for(; row < n; row++){
      graph->adj[row] = calloc (n, sizeof(int));
      for(; column < n; column++){
        graph->adj[row][column] = INT_MIN; /**< Inizializzazione della nuova colonna al piu' grande numero negativo rappresentabile su 32 bit. */
      }
      assert(graph->adj[row]!=NULL);
    }
    return graph;
}

/**
 * @brief Distrugge un grafo liberando tutta la memoria
 *
 * @param graph il grafo da eliminare
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_w_dirgraph_destroy(upo_w_dirgraph_t graph){
    if(graph == NULL){
      return -1;
    }

    else if(graph != NULL){ /**< Deallocazione della matrice di adiacenza e successivamente del grafo. */
      int row = upo_w_num_vertices(graph) - 1;
      if(row < 0) { /**< Modifica dalla prima versione. */
          row = 0;
      }
      for(; row >= 0; row--){
        free(graph->adj[row]);
      }
      free(graph->adj);
      free(graph);
      return 1;
    }
    else{
      return 0; /**< Non ritorna mai 0, poichè non si può verificare l'andamento della free. */
    }
}


/**
 * @brief Restituisce il numero di vertici del grafo
 *
 * @param graph il grafo
 * @return il numero di vertici del grafo, -1 se il grafo e' nullo
 */
int upo_w_num_vertices(upo_w_dirgraph_t graph){
    if(graph == NULL){
      return -1;
    }
    return graph->n;
}

/**
 * @brief Restituisce il numero di archi del grafo
 *
 * @param graph il grafo
 * @return il numero di archi del grafo, -1 se il grafo e' nullo
 */
int upo_w_num_edges(upo_w_dirgraph_t graph) {
    if(graph == NULL){
      return -1;
    }
    int edges = 0;
    int n = upo_w_num_vertices(graph);
    int row = 0;
    int column = 0;
    for(; row < n; row++){
      for(column = 0; column < n; column++){
        if(graph->adj[row][column] == 1){
          edges++;
        }
      }
    }
    return edges;
}

/**
 * @brief Restituisce il grado entrante di un vertice
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return il grado entrante di vertex, -1 se il grafo e' nullo
 */
int upo_w_get_in_degree(upo_w_dirgraph_t graph, int vertex) {
    if(graph == NULL){
      return -1;
    }
    int inDegree = 0;
    int n = upo_w_num_vertices(graph);
    int row = 0;
    if(upo_w_has_vertex(graph, vertex)){
        for(; row < n; row++){
            if(graph->adj[row][vertex] == 1){
                inDegree++;
            }
        }
    }
    return inDegree;
}

/**
 * @brief Restituisce il grado uscente di un vertice
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return il grado uscente di vertex, -1 se il grafo e' nullo
 */
int upo_w_get_out_degree(upo_w_dirgraph_t graph, int vertex) {
    if(graph == NULL){
      return -1;
    }
    int outDegree = 0;
    int n = upo_w_num_vertices(graph);
    int column = 0;
    if(upo_w_has_vertex(graph, vertex)){
        for(; column < n; column++){
            if(graph->adj[vertex][column] == 1){
                outDegree++;
            }
        }
    }
    return outDegree;
}

/**
 * @brief Restituisce il grado complessivo di un vertice
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return il grado complessivo di vertex, -1 se il grafo e' nullo
 */
int upo_w_get_degree(upo_w_dirgraph_t graph, int vertex) {
    if(graph == NULL){
      return -1;
    }
    return (upo_w_get_in_degree(graph, vertex) + upo_w_get_out_degree(graph, vertex));
}

/**
 * @brief Controlla se il grafo e' vuoto
 *
 * @param graph il grafo
 * @return 1 se il grafo e' vuoto, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_is_graph_empty(upo_w_dirgraph_t graph) {
    if(graph == NULL){
      return -1;
    }
    else if(graph->n == 0){
      return 1;
    }
    else{
      return 0; /**< Nel caso in cui il garfo contenga dei vertici. */
    }
}

/**
 * @brief Restituisce una lista contenente i vertici adiacenti a vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente i vertici adiacenti a vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_w_get_adj_vert(upo_w_dirgraph_t graph, int vertex) {
    upo_list_t adjVert = NULL;
      if(upo_w_is_graph_empty(graph) == 0 && upo_w_has_vertex(graph, vertex) == 1){
        adjVert = upo_create_list(sizeof(int),NULL); /**< Creazione della lista. */
        int n = upo_w_num_vertices(graph);
        int column = 0;
        for(; column < n; column++){ /**< Scorrimento delle colonne data una riga in cerca dei vertici adiacenti ad un dato vertice. */
          if(graph->adj[vertex][column] != INT_MIN){ /**< Selezione dei vertici da inserire nella lista. */
            int *value = malloc(sizeof(int)); /**< Allocazione di memoria per contenere il vertice da passare alla lista per non perderlo all'uscita della funzione*/
            assert(value!=NULL);
            *value = column; /**< Salvataggio del valore del vertice nella memoria appena allocata. */
            upo_add_last(adjVert, value); /** Creazione di un nuovo nodo della lista contenente il vertice e inserimento in coda. */
          }
        }
      }
      return adjVert;
}

/**
 * @brief Restituisce una lista contenente gli archi uscenti da vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi uscenti da vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_w_get_inc_out_edg(upo_w_dirgraph_t graph, int vertex) {
  upo_list_t incOutEdges = NULL;
  if(upo_w_is_graph_empty(graph) == 0){
      incOutEdges = upo_create_list(sizeof(upo_dir_edge_s),NULL); /**< Creazione della lista. */
      int n = upo_w_num_vertices(graph);
      int column = 0;
      for(; column < n; column++){ /**< Scorrimento delle colonne data una riga in cerca degli archi uscenti da un dato vertice. */
          if(graph->adj[vertex][column] == 1){ /**< Selezione degli archi da inserire nella lista. */
            upo_w_dir_edge_t edge = malloc(sizeof(upo_dir_edge_s)); /**< Allocazione di memoria per contenere l'arco da passare alla lista per non perderlo all'uscita della funzione*/
            assert(edge!=NULL);
            edge->from = vertex; /**< Salvataggio dell'arco nella memoria appena allocata. */
            edge->to = column;
            upo_add_last(incOutEdges, edge); /** Creazione di un nuovo nodo della lista contenente l'arco e inserimento in coda. */
          }
      }
  }
  return incOutEdges;
}

/**
 * @brief Restituisce una lista contenente gli archi entranti in vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi archi entranti in vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_w_get_inc_in_edg(upo_w_dirgraph_t graph, int vertex) {
  upo_list_t incInEdges = NULL;
  if(upo_w_is_graph_empty(graph) == 0){
    incInEdges = upo_create_list(sizeof(upo_dir_edge_s),NULL); /**< Creazione della lista. */
    int n = upo_w_num_vertices(graph);
    int row = 0;
    for(; row < n; row++){ /**< Scorrimento delle righe data una colonna in cerca degli archi entranti da un dato vertice. */
      if(graph->adj[row][vertex] == 1){ /**< Selezione degli archi da inserire nella lista. */
        upo_w_dir_edge_t edge = malloc(sizeof(upo_dir_edge_s)); /**< Allocazione di memoria per contenere l'arco da passare alla lista per non perderlo all'uscita della funzione*/
        assert(edge!=NULL);
        edge->from = row; /**< Salvataggio dell'arco nella memoria appena allocata. */
        edge->to = vertex;
        upo_add_last(incInEdges, edge); /** Creazione di un nuovo nodo della lista contenente l'arco e inserimento in coda. */
      }
    }
  }
  return incInEdges;
}

/**
 * @brief Restituisce una lista contenente gli archi incidenti a vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi incidenti a vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_w_get_inc_edg(upo_w_dirgraph_t graph, int vertex) {
  upo_list_t incEdges = NULL;
  if(upo_w_is_graph_empty(graph) == 0){
    incEdges = upo_w_get_inc_out_edg(graph, vertex);
    if( upo_list_size(incEdges) > 0){ /**< Se la lista degli archi uscenti dal vertice non è vuota collego alla sua coda la lista degli archi entranti in quel vertice. */
      upo_list_t tempList = upo_w_get_inc_in_edg(graph, vertex);
      incEdges->tail->next = tempList->head;
      incEdges->tail = tempList->tail;
      incEdges->logicalLength += tempList->logicalLength;
    }
    else{
      incEdges = upo_w_get_inc_in_edg(graph, vertex);
    }
  }
  return incEdges;
}

/**
 * @brief Aggiunge un nuovo vertice al grafo di indice size+1 (dove size è il numero di vertici)
 *
 * @param graph il grafo
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */

int upo_w_add_vertex(upo_w_dirgraph_t graph) {  /**TASK 1*/
    if(graph == NULL){
      return -1;
    }
    int n = upo_w_num_vertices(graph);
    graph->n++;
    if(n > 0){
        int row = 0;
        for(; row < n; row++){ /**< Ingrandimento della matrice di adiacenza di una colonna. */
            graph->adj[row] = realloc(graph->adj[row], (sizeof(int*[n+1])));
            assert(graph->adj[row]!=NULL);
            graph->adj[row][n] = INT_MIN; /**< Inizializzazione della nuova colonna al piu' grande numero negativo rappresentabile su 32 bit. */
        }
        graph->adj = realloc(graph->adj, (sizeof(int**[n+1]))); /**< Ingrandimento della matrice di adiacenza di una riga. */
        assert(graph->adj!=NULL);
        graph->adj[n] = calloc (n+1, sizeof(int));
        assert(graph->adj[n]!=NULL);
        int line = 0;
        for(; line < n+1; line++){
          graph->adj[n][line] = INT_MIN; /**< Inizializzazione della nuova riga al piu' grande numero negativo rappresentabile su 32 bit. */
        }
        return 1;
    }
    else if(n == 0) {
      return 1;
    }
    return 0; /**< Non ritorna mai 0, ma previsto per eventuali implementazioni future e per conformità con il resto del codice. */
}

/**
 * @brief Controlla l'esistenza di un vertice di indice vertex nel grafo
 *
 * @param graph il grafo
 * @param vertex il vertice da cercare
 * @return 1 se il grafo contiene il vertice, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_has_vertex(upo_w_dirgraph_t graph, int vertex) {
    if(graph == NULL){
      return -1;
    }
    else if (vertex >= graph->n || graph->n == 0 || vertex < 0) { /**< Controllo che valore del vartice non sia più grande del numero di vertici presenti, che il grafo non sia vuoto, che il valore del vertice non sia < 0. */
        return 0;
    }
    else {
        return 1;
    }
}

/**
 * @brief Elimina un vertice di indice vertex dal grafo e tutti gli archi ad esso incidenti. Attenzione, le liste di adiacenza vanno aggiornate.
 *
 * @param graph il grafo
 * @param vertex il vertice da eliminare
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_remove_vertex(upo_w_dirgraph_t graph, int vertex) {
  if (graph == NULL) {
      return -1;
  }
  else if (upo_w_has_vertex (graph, vertex) == 1) {
      int n = upo_w_num_vertices(graph);
      if(n == 1) {
          graph->adj[0][0] = 0;
          graph->n--;
          return 1;
      }
      int** newMatrix = malloc (sizeof(int**[(n-1)])); /**< Allocazione della nuova matrice di adiacenza e controllo con assert. */
      assert(newMatrix!=NULL);
      int oldRow = 0;
      int oldColumn = 0;
      int newRow = 0;
      int newColumn = 0;
      for (oldRow = 0; oldRow < n; oldRow++) { /**< Scorrimento delle righe della vecchia matrice. */
          if (oldRow != vertex) {
              newMatrix[newRow] = malloc (sizeof(int*[n-1]));
              assert(newMatrix[newRow]!=NULL);
              newColumn = 0;
              for (oldColumn = 0; oldColumn < n; oldColumn++) { /**< Scorrimento delle colonne della vecchia matrice. */
                  if (oldColumn != vertex) {
                      newMatrix[newRow][newColumn] = graph->adj[oldRow][oldColumn]; /**< Copia del vecchio valore nella nuova matrice. */
                      newColumn++;
                  }
              }
              newRow++;
          }
          free(graph->adj[oldRow]);
      }
      free(graph->adj);
      graph->adj = newMatrix;
      graph->n--;
      return 1;
  }
  else {
      return 0; /**< Negli stessi casi previsti da upo_has_vertex. */
  }
}

/**
 * @brief Aggiunge un arco al grafo. Se l'arco gia' esiste non fa nulla
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @param weight il peso dell'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_add_edge(upo_w_dirgraph_t graph, int vertex1, int vertex2, int weight) { /**TASK 2*/
  if (graph == NULL) {
      return -1;
  }
  else if (upo_w_has_vertex(graph, vertex1) && upo_w_has_vertex(graph, vertex2) && upo_w_has_edge(graph, vertex1, vertex2) == 0 && weight != INT_MIN) {
          graph->adj[vertex1][vertex2] = weight; /**< Nella casella corrispondente dell'arco salvo il peso. */
          return 1;
  }
  return 0; /**< Negli stessi casi di upo_has_edge. */
}

/**
 * @brief Controlla l'esistenza di un arco nel grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se il grafo contiene l'arco, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_has_edge(upo_w_dirgraph_t graph, int vertex1, int vertex2) {
  if (graph == NULL) {
      return -1;
  }
  else if (upo_w_has_vertex( graph, vertex1) == 1 && upo_w_has_vertex( graph, vertex2) == 1) {
      if (graph->adj[vertex1][vertex2] != INT_MIN) { /**< Controllo separato per evitare accesso a zone di memoria esterne che porterebbero ad un segmentation fault. */
          return 1;
      }
  }
  return 0; /**< Se non esiste l'arco tra vertex1 e vertex2, oppure se il grafo non contiene uno o entrambi i vertici. */
}

/**
 * @brief Rimuove un arco dal grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_remove_edge(upo_w_dirgraph_t graph, int vertex1, int vertex2) {
  if (graph == NULL) {
      return -1;
  }
  else if (upo_w_has_edge(graph, vertex1, vertex2) == 1) {
      graph->adj[vertex1][vertex2] = INT_MIN;
      return 1;
  }
  return 0; /**< Negli stessi casi di upo_has_edge. */
}

/**
 * @brief Restituisce il peso di un'arco
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_has_weight_edge(upo_w_dirgraph_t graph, int vertex1, int vertex2) { /**TASK 3*/
  if (graph == NULL) {
      return INT_MIN;
  }
  else if (upo_w_has_edge(graph, vertex1, vertex2) == 1) {
      return graph->adj[vertex1][vertex2];
  }
  return INT_MIN; /**< Negli stessi casi di upo_has_edge. */
}

/**
 * @brief Controlla se due vertici sono adiacenti
 *
 * @param graph il grafo
 * @param vertex1 il primo vertice
 * @param vertex2 il secondo vertice
 * @return 1 se i vertici sono adiacenti, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_w_are_adj(upo_w_dirgraph_t graph, int vertex1, int vertex2) {
  if (graph == NULL) {
      return -1;
  }
  else if (upo_w_has_edge(graph, vertex1, vertex2) == 1) {
      return 1;
  }
  return 0; /**< Negli stessi casi di upo_has_edge. */
}

/**
 * @brief Restituisce una stringa rappresentante il grafo, nella forma Vertice: v;\n v -> i;\n v -> j\n dove i e j sono i vertici adiacenti a v
 *
 * @param graph il grafo
 * @return una stringa rappresentante il grafo
 */
char* upo_w_print_graph(upo_w_dirgraph_t graph) {
  char* graphToString = calloc(DIM_STRING,sizeof(char)); /**< Allocazione della stringa da ritornare con inizializzazione della memoria allocata a 0 e controllo con assert. */
  assert(graphToString!=NULL);
  if (graph != NULL) {
      int vertex = 0;
      for (; vertex < graph->n; vertex++) { /**< Scorrimento di tutti i vertici del grafo. */
          char buffer1 [DIM_BUF];
          sprintf(buffer1,"Vertice: %d;\n",vertex); /**< Salvataggio nel buffer della stringa "Vertice: %d;\n". */
          strcat(graphToString,buffer1); /**< Concatenazione del buffer con la stringa da ritornare. */
          upo_list_t adjVert = upo_w_get_adj_vert(graph, vertex); /**< Recupero dei vertici adiacenti al vertice che si sta controllando. */
          while (upo_list_size(adjVert) != 0) { /**< Scorrimento della lista creata fino a che non sarà vuota, data la rimozione del primo elemento attraverso upo_remove_first. */
              int nextAdjVert = *((int*)upo_remove_first(adjVert)); /**< Rimozione dalla lista del primo elemento. */
              char buffer2 [DIM_BUF];
              sprintf(buffer2," %d - (%d) > %d;\n", vertex, graph->adj[vertex][nextAdjVert], nextAdjVert);
              strcat(graphToString,buffer2);
          }
          upo_destroy_list(adjVert); /**< Deallocazione della lista creata precedentemente. */
      }
  }

  return graphToString;
}

/**
 * @brief alloca e valorizza il vettore delle distane e dei padri per una ricerca dei cammini minimi a partire da una sorgente
 *
 * @param graph e' il grafo pesato
 * @param source e' la sorgenta da cui calcolare i cammini minimi
 * @param p_padri e' il puntatore al vettore dei padri
 * @param p_distanze e' il puntatore al vettore delle distanze
 * @return 1 se l'operazione e' andata a buon fine, restituisce un valore negativo in caso contrario
 */
int upo_cmDijkstra(upo_w_dirgraph_t graph, int source, int** p_padri, int** p_distanze){
  if (upo_w_is_graph_empty(graph)==-1) return -1; /**il grafo e' NULL*/
  if (upo_w_is_graph_empty(graph)==1) return -2; /**il grafo e' vuoto*/
  if (upo_w_has_vertex(graph, source)!=1)return -3; /**source non esiste */
  int* padri=NULL;
  int* distanze=NULL;
  int i=0;
  int* vertex=NULL;
  int* vertex_find=NULL;
  int weight=-1;
  int negativ_weight=0;
  int counter=0;
  int min=-1;
  int stop=0;
  int posizione_minima=0;
  int* vertex_min = &posizione_minima;
  upo_list_t adj_list=NULL;
  int priority[graph->n];
  padri=malloc(sizeof(int)*graph->n);
  if(padri==NULL) return -4;/**allocazione del vettore dei padri fallita*/
  vertex=padri;
  distanze=malloc(sizeof(int)*graph->n);
  if(distanze==NULL) return -5;/**allocazione del vettore delle distanze fallita*/
  for(i=0; i<graph->n; i++){/**cilo di inizializzazione settando tutti i padri a -1, le distanze e le priorita' a infinito*/
    padri[i]=-1;
    distanze[i]=INT_MIN;
    priority[i]=INT_MAX;
  }
  distanze[source]=0;
  priority[source]=INT_MIN;
  adj_list=upo_w_get_adj_vert(graph, source);
  while(upo_list_size(adj_list)>0){ /**imposto le distanze, le priorita' e le distanze dei vertici adiacenti a source */
     vertex=upo_remove_first(adj_list);
     weight=upo_w_has_weight_edge(graph,source, *vertex);
     if(weight<0) negativ_weight=1; /**se incontro un arco di peso negativo ne tengo traccia per annullare l'operazione*/
     else priority[*vertex]=weight;
     padri[*vertex]=source;
     distanze[*vertex]=weight;
     free(vertex);
   }
   i=0;
   while(i<graph->n-1 && negativ_weight==0 && stop==0){
     min=upo_get_min(priority, graph->n);
     if(min==-1) stop=1;
     else {
       *vertex_min=min;
       upo_destroy_list(adj_list);
       adj_list=upo_w_get_adj_vert(graph, *vertex_min);
       while(upo_list_size(adj_list)>0){
         vertex_find=upo_remove_first(adj_list);
         weight=upo_w_has_weight_edge(graph, *vertex_min, *vertex_find);
         if(weight<0) negativ_weight=1; /**se incontro un arco di peso negativo ne tengo traccia per annullare l'operazione*/
         if(distanze[*vertex_find]==INT_MIN||distanze[*vertex_find]>distanze[*vertex_min]+weight){
           priority[*vertex_find]=priority[*vertex_min]+weight;
           padri[*vertex_find]=*vertex_min;
           distanze[*vertex_find]=distanze[*vertex_min]+weight;
         }
         free(vertex_find);
       }
       i++;
       priority[*vertex_min]=INT_MIN;
       vertex_min++;
     }
   }
   upo_destroy_list(adj_list);
   if(negativ_weight==1){
     free(padri);
     free(distanze);
     return -6; /**si e' incontrato un peso negativo quindi non si puo' procedere con l'operazione*/
   }
   else {
     *p_padri=padri;
     *p_distanze=distanze;
   }
   return 1;
}

 /**
  * @brief cerca il valore minimo nella coda di priorita' e restituisce la sua posizione
  *
  * @param graph e' il grafo pesato
  * @param priority e' il puntatore al vettore della coda di priorita'
  * @param dim e' la dimensione del vettore della coda di priorita'
  * @return -1 se non si trovano altri elementi in coda o restituisce la posizione con priorita' maggiore(valore minore)
  */
 int upo_get_min(int* priority, int dim){
   int min=INT_MAX;
   int posizione=-1;
   int i=0;
   for(i=0; i<dim; i++){
     if (priority[i]<min && priority[i]!=INT_MIN){
       min=priority[i];
       posizione=i;
     }
   }
   return posizione;
 }
/**
Dijkstra (G, W, s)
  INIZIALIZZA (G)  **OK
  D <- empty_priority_queue()   **OK
  d[s] <- 0 **OK
  for ogni v in V[G]  **OK
    enqueue(D,v,d[v])  **OK
  while NotEmpty(D) do begin
    u <- dequeue_min(D)  **OK
    S <- S ∪ {u} //aggiungo u all’albero definitivamente  **OK
    for ogni v adj ad u then  **OK
      if d[v] > d[u] + W(u,v) then **OK
      π[v] <- u **OK
      d[v] <- d[u] + W(u,v)  **OK
      decrease_key(D,v,d[v]) **OK
    end for
  end*/
