#include "upo_dir_graph_adj_matrix.h"
#include <assert.h>
/**
 * @brief Crea un nuovo grafo orientato
 *
 * @return un nuovo grafo diretto vuoto
 *
 */

upo_dirgraph_t upo_dirgraph_create(int n) {
    upo_dirgraph_t graph = NULL;
    graph = malloc(sizeof(upo_dirgraph_s));
    assert(graph!=NULL);
    graph->n = 0;
    if(n < 1){
      n = 1;
    }
    graph->adj=NULL;
    graph->adj = malloc(sizeof(int**[n]));
    assert(graph->adj!=NULL);
    for(int row = 0; row < n; row++){
      graph->adj[row] = calloc (n, sizeof(int));
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
int upo_dirgraph_destroy(upo_dirgraph_t graph){ //da rivedere per quando deve ritornare 0
    if(graph == NULL){
      return -1;
    }
    else{
      int row = upo_num_vertices(graph) - 1;
        for(; row >= 0; row--){
        free(graph->adj[row]);
      }
      free(graph->adj);
      free(graph);
      return 1;
    }
}


/**
 * @brief Restituisce il numero di vertici del grafo
 *
 * @param graph il grafo
 * @return il numero di vertici del grafo, -1 se il grafo e' nullo
 */
int upo_num_vertices(upo_dirgraph_t graph){
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
int upo_num_edges(upo_dirgraph_t graph) {
    if(graph == NULL){
      return -1;
    }
    int edges = 0;
    int n = upo_num_vertices(graph);
    for(int row = 0; row < n; row++){
      for(int column = 0; column < n; column++){
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
int upo_get_in_degree(upo_dirgraph_t graph, int vertex) {
    if(graph == NULL){
      return -1;
    }
    int inDegree = 0;
    int n = upo_num_vertices(graph);
    for(int row = 0; row < n; row++){
      if(graph->adj[row][vertex] == 1){
        inDegree++;
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
int upo_get_out_degree(upo_dirgraph_t graph, int vertex) {
    if(graph == NULL){
      return -1;
    }
    int outDegree = 0;
    int n = upo_num_vertices(graph);
    for(int column = 0; column < n; column++){
      if(graph->adj[vertex][column] == 1){
        outDegree++;
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
int upo_get_degree(upo_dirgraph_t graph, int vertex) {
    if(graph == NULL){
      return -1;
    }
    return (upo_get_in_degree(graph, vertex) + upo_get_out_degree(graph, vertex));
}

/**
 * @brief Controlla se il grafo e' vuoto
 *
 * @param graph il grafo
 * @return 1 se il grafo e' vuoto, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_is_graph_empty(upo_dirgraph_t graph) {
    if(graph == NULL){
      return -1;
    }
    else if(graph->n == 0){
      return 1;
    }
    else{
      return 0;
    }
}

/**
 * @brief Restituisce una lista contenente i vertici adiacenti a vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente i vertici adiacenti a vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_get_adj_vert(upo_dirgraph_t graph, int vertex) {
    upo_list_t adjVert = NULL;
      if(upo_is_graph_empty(graph) == 0){
        adjVert = upo_create_list(sizeof(int),NULL); /**< Creazione della lista. */
        int n = upo_num_vertices(graph);
        for(int column = 0; column < n; column++){ /**< Scorrimento delle colonne data una riga in cerca dei vertici adiacenti ad un dato vertice. */
          if(graph->adj[vertex][column] == 1){ /**< Selezione dei vertici da inserire nella lista. */
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
upo_list_t upo_get_inc_out_edg(upo_dirgraph_t graph, int vertex) {
  upo_list_t incOutEdges = NULL;
  if(upo_is_graph_empty(graph) == 0){
      incOutEdges = upo_create_list(sizeof(upo_dir_edge_s),NULL); /**< Creazione della lista. */
      int n = upo_num_vertices(graph);
      for(int column = 0; column < n; column++){ /**< Scorrimento delle colonne data una riga in cerca degli archi uscenti da un dato vertice. */
          if(graph->adj[vertex][column] == 1){ /**< Selezione degli archi da inserire nella lista. */
            upo_dir_edge_t edge = malloc(sizeof(upo_dir_edge_s)); /**< Allocazione di memoria per contenere l'arco da passare alla lista per non perderlo all'uscita della funzione*/
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
upo_list_t upo_get_inc_in_edg(upo_dirgraph_t graph, int vertex) {
  upo_list_t incInEdges = NULL;
  if(upo_is_graph_empty(graph) == 0){
    incInEdges = upo_create_list(sizeof(upo_dir_edge_s),NULL); /**< Creazione della lista. */
    int n = upo_num_vertices(graph);
    for(int row = 0; row < n; row++){ /**< Scorrimento delle righe data una colonna in cerca degli archi entranti da un dato vertice. */
      if(graph->adj[row][vertex] == 1){ /**< Selezione degli archi da inserire nella lista. */
        upo_dir_edge_t edge = malloc(sizeof(upo_dir_edge_s)); /**< Allocazione di memoria per contenere l'arco da passare alla lista per non perderlo all'uscita della funzione*/
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
upo_list_t upo_get_inc_edg(upo_dirgraph_t graph, int vertex) {
  upo_list_t incEdges = NULL;
  if(upo_is_graph_empty(graph) == 0){
    incEdges = upo_get_inc_out_edg(graph, vertex);
    if( upo_list_size(incEdges) > 0){
      upo_list_t tempList = upo_get_inc_in_edg(graph, vertex);
      incEdges->tail->next = tempList->head;
      incEdges->tail = tempList->tail;
      incEdges->logicalLength += tempList->logicalLength;
    }
    else{
      incEdges = upo_get_inc_in_edg(graph, vertex);
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

int upo_add_vertex(upo_dirgraph_t graph) { //Verificare quando deve ritornare 0
    if(graph == NULL){
      return -1;
    }
    int n = upo_num_vertices(graph);
    graph->n++;
    if(n > 0){
        for(int row = 0; row < n; row++){
            graph->adj[row] = realloc(graph->adj[row], (sizeof(int*[n+1])));
            assert(graph->adj[row]!=NULL);
            graph->adj[row][n] = 0;
        }
        graph->adj = realloc(graph->adj, (sizeof(int**[n+1])));
        assert(graph->adj!=NULL);
        graph->adj[n] = calloc (n+1, sizeof(int));
        assert(graph->adj[n]!=NULL);
    }
    return 1;
}

/**
 * @brief Controlla l'esistenza di un vertice di indice vertex nel grafo
 *
 * @param graph il grafo
 * @param vertex il vertice da cercare
 * @return 1 se il grafo contiene il vertice, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_has_vertex(upo_dirgraph_t graph, int vertex) {
    if(graph == NULL){
      return -1;
    }
    else if (vertex >= graph->n || graph->n == 0 || vertex < 0) {
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
int upo_remove_vertex(upo_dirgraph_t graph, int vertex) {
  if (graph == NULL) {
      return -1;
  }
  else if (upo_has_vertex (graph, vertex) == 1) {
      int n = upo_num_vertices(graph);
      int** newMatrix = malloc (sizeof(int**[(n-1)])); /**< Allocazione della nuova matrice di adiacenza. */
      assert(newMatrix1!=NULL);
      int oldRow = 0;
      int oldColumn = 0;
      int newRow = 0;
      int newColumn = 0;
      for (oldRow = 0; oldRow < n; oldRow++) {
          if (oldRow != vertex) {
              newMatrix[newRow] = malloc (sizeof(int*[n-1]));
              assert(newMatrix[newRow]!=NULL);
              for (oldColumn = 0; oldColumn < n; oldColumn++) {
                  if (oldColumn != vertex) {
                      newMatrix[newRow][newColumn] = graph->adj[oldRow][oldColumn]; /**< Copia della vecchia matrice nella nuova. */
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
      return 0;
  }
}

/**
 * @brief Aggiunge un arco al grafo. Se l'arco gia' esiste non fa nulla
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_add_edge(upo_dirgraph_t graph, int vertex1, int vertex2) {
  if (graph == NULL) {
      return -1;
  }
  else if (upo_has_edge(graph, vertex1, vertex2) == 0) {
          graph->adj[vertex1][vertex2] = 1;
          return 1;
  }
  return 0;
}

/**
 * @brief Controlla l'esistenza di un arco nel grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se il grafo contiene l'arco, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_has_edge(upo_dirgraph_t graph, int vertex1, int vertex2) {
  if (graph == NULL) {
      return -1;
  }
  else if (upo_has_vertex( graph, vertex1) == 1 && upo_has_vertex( graph, vertex2) == 1) {
      if (graph->adj[vertex1][vertex2] == 1) {
          return 1;
      }
  }
  return 0;
}

/**
 * @brief Rimuove un arco dal grafo
 *
 * @param graph il grafo
 * @param vertex1 da dove esce l'arco
 * @param vertex2 dove entra l'arco
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_remove_edge(upo_dirgraph_t graph, int vertex1, int vertex2) {
  if (graph == NULL) {
      return -1;
  }
  else if (upo_has_edge(graph, vertex1, vertex2) == 1) {
      graph->adj[vertex1][vertex2] = 0;
      return 1;
  }
  return 0;
}

/**
 * @brief Controlla se due vertici sono adiacenti
 *
 * @param graph il grafo
 * @param vertex1 il primo vertice
 * @param vertex2 il secondo vertice
 * @return 1 se i vertici sono adiacenti, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_are_adj(upo_dirgraph_t graph, int vertex1, int vertex2) {
  if (graph == NULL) {
      return -1;
  }
  else if (upo_has_edge(graph, vertex1, vertex2) == 1) {
      return 1;
  }
  return 0;
}

/**
 * @brief Restituisce una stringa rappresentante il grafo, nella forma Vertice: v;\n v -> i;\n v -> j\n dove i e j sono i vertici adiacenti a v
 *
 * @param graph il grafo
 * @return una stringa rappresentante il grafo
 */
char* upo_print_graph(upo_dirgraph_t graph) {
  char* graphToString = calloc(1024,sizeof(char));
  assert(graphToString!=NULL);
  if (graph != NULL) {
      for (int vertex = 0; vertex < graph->n; vertex++) {
          char buffer1 [20];
          sprintf(buffer1,"Vertice: %d;\n",vertex);
          strcat(graphToString,buffer1);
          upo_list_t adjVert = upo_get_adj_vert(graph, vertex);
          while (upo_list_size(adjVert) != 0) {
              int nextAdjVert = *((int*)upo_remove_first(adjVert));
              char buffer2 [20];
              sprintf(buffer2," %d -> %d;\n", vertex, nextAdjVert);
              strcat(graphToString,buffer2);
          }
          upo_destroy_list(adjVert);
      }
  }

  return graphToString;
}
