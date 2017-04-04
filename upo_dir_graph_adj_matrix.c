#include "upo_dir_graph_adj_matrix.h"
#define NELEMS(x) (sizeof(x) / sizeof((x)[0]) -1)

/**
 * @brief Crea un nuovo grafo orientato
 *
 * @return un nuovo grafo diretto vuoto
 *
 */
/** upo_dirgraph_t upo_dirgraph_create(int n) {
  * upo_dirgraph_t graph_p = NULL;
  * int i;
  * if(n == 0){return graph_p;}
  * graph_p = malloc(sizeof(upo_dirgraph_s));
  * graph_p.n = n;
  * graph_p.adj = malloc(n * (sizeof(int*)));
  * for(i = 0, i < n, i++){
  *     (graph_p.adj) + (i * sizeof(int*)) = malloc(n * (sizeof(int)));
  * }
  * return graph_p;
  * }
**/

upo_dirgraph_t upo_dirgraph_create(int n) {
    upo_dirgraph_t graph = NULL;
    graph = malloc(sizeof(upo_dirgraph_s));
    graph->n = 0;
    if(n < 1){
      n = 1;
    }
    graph->adj = malloc(sizeof(int**[n]));
    for(int row = 0; row < n; row++){
      graph->adj[row] = malloc (sizeof(int*[n]));
      for (int column = 0; column < n; column++){
        graph->adj[row][column] = 0;
      }
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
int upo_dirgraph_destroy(upo_dirgraph_t graph){
    if(graph == NULL){
      return -1;
    }
    else{
      for(int row = NELEMS(graph->adj); row >= 0; row--){
        free(graph->adj[i]);
      }
      free(graph->adj);
      free(graph);
    }
    if(graph == NULL){
      return 1;
    }
    else{
      return 0;
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
    for(int row = 0; i < n; row++){
      for(int column = 0; j < n; column++){
        if(graph->adj[row][column] == 1){
          archi++;
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
    int archi = upo_get_out_degree(graph, vertex);
    if(archi == 0) return NULL;
    if(graph == NULL) return NULL;
    upo_list_t list == NULL;
    list = upo_create_list(sizeof(int), NULL);
    int j;
    int n = upo_num_vertices(graph);
    for(j = 0, j < n, j++){
      if(graph.adj[vertex][j] == 1){ //aggiungo nodo alla lista
        upo_add_first(list, &j);
      }
    }
    return list;
}

/**
 * @brief Restituisce una lista contenente gli archi uscenti da vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi uscenti da vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_get_inc_out_edg(upo_dirgraph_t graph, int vertex) {
    upo_list_t list = NULL;
    list = upo_create_list(sizeof(int), NULL);
    int j;
    int n = upo_num_vertices(graph);
    if(graph == NULL) return NULL;
    for(j = 0, j < n, j++){
      if(graph.adj[vertex][j] == 1){
        upo_add_first(list, &j);
      }
    }
    return list;
}

/**
 * @brief Restituisce una lista contenente gli archi entranti in vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi archi entranti in vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_get_inc_in_edg(upo_dirgraph_t graph, int vertex) {
    upo_list_t list = NULL;
    list = upo_create_list(sizeof(int), NULL);
    int i;
    int n = upo_num_vertices(graph);
    if(graph == NULL) return NULL;
    for(i = 0, i < n, i++){
      if(graph.adj[i][vertex] == 1){
        upo_add_first(list, &i);
      }
    }
    return list;
}

/**
 * @brief Restituisce una lista contenente gli archi incidenti a vertex
 *
 * @param graph il grafo
 * @param vertex il vertice
 * @return una lista contenente gli archi incidenti a vertex, NULL se il grafo e' vuoto
 */
upo_list_t upo_get_inc_edg(upo_dirgraph_t graph, int vertex) {
    upo_list_t list = NULL;
    list = upo_create_list(sizeof(int), NULL);
    int i;
    int j;
    int n = upo_num_vertices(graph);
    if(graph == NULL) return NULL;
    for(i = 0, i < n, i++){
      if(graph.adj[i][vertex] == 1){
        upo_add_first(list, &i);
      }
    }
    for(j = 0, j < n, j++){
      if(graph.adj[vertex][j] == 1){
        upo_add_first(list, &j);
      }
    }
    return list;
}

/**
 * @brief Aggiunge un nuovo vertice al grafo di indice size+1 (dove size è il numero di vertici)
 *
 * @param graph il grafo
 * @return 1 se l'operazione è andata a buon fine, -1 se il grafo e' nullo, 0 altrimenti
 *
 */
int upo_add_vertex(upo_dirgraph_t graph) {
    int size = upo_num_vertices(graph);
    if(graph == NULL) return -1;
    graph.adj[size+1] = malloc (upo_dirgraph_t) malloc(n * (sizeof(int)));

    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Controlla l'esistenza di un vertice di indice vertex nel grafo
 *
 * @param graph il grafo
 * @param vertex il vertice da cercare
 * @return 1 se il grafo contiene il vertice, -1 se il grafo e' nullo, 0 altrimenti
 */
int upo_has_vertex(upo_dirgraph_t graph, int vertex) {
    if(graph == NULL) return -1;
    if(graph.adj[vertex][vertex] != NULL) return 1;
    else{
      return 0;
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
    fprintf(stderr, "To be implemented!\n");
    abort();
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
    fprintf(stderr, "To be implemented!\n");
    abort();
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
    fprintf(stderr, "To be implemented!\n");
    abort();
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
    fprintf(stderr, "To be implemented!\n");
    abort();
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
    fprintf(stderr, "To be implemented!\n");
    abort();
}

/**
 * @brief Restituisce una stringa rappresentante il grafo, nella forma Vertice: v;\n v -> i;\n v -> j\n dove i e j sono i vertici adiacenti a v
 *
 * @param graph il grafo
 * @return una stringa rappresentante il grafo
 */
char* upo_print_graph(upo_dirgraph_t graph) {
    fprintf(stderr, "To be implemented!\n");
    abort();
}
