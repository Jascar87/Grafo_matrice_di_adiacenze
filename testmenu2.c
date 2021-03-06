#include <stdio.h>
#include <stdlib.h>
#include "upo_visit.c"
#define TRUE 1
#define FALSE 0
#define RED "\033[31;1m" /**stampa errori*/
#define YELLOW "\033[33;1m" /**stampe risultati*/
#define MAGENTA "\033[35;1m" /**stampa sottomenu*/
#define CYAN "\033[36;1m" /**stampa primo menu*/
#define RESET "\033[0m" /**valore di default delle stampe*/

void selection(int* digit) {
    char dump;
    printf("\nScegliere un comando: ");
    scanf("%d", digit);
    scanf("%c",&dump);
    fflush(stdin);
}

void scc(int padre, int* vet, int dim){
  int i;
  for(i = 0; i < dim; i++){
    if(vet[i] == padre){
      printf(YELLOW ",%d" RESET, i);
      scc(i, vet, dim);
    }
  }
  return;
}

void stampa_scc(int* vet, upo_dirgraph_t graph) {
  if(vet == NULL) {
      if(upo_is_graph_empty(graph)==-1) {
          printf("\a\"");
          printf(RED "\n\tIl grafo analizzato e' nullo\n" RESET);
          return;
      }
      else if(upo_is_graph_empty(graph)==1) {
          printf("\a\"");
          printf(RED "\n\tIl grafo analizzato e' vuoto\n" RESET);
          return;
      }
  }
  int i;
  printf(YELLOW "Componenti fortemente connesse\n" RESET);
  printf(YELLOW "{" RESET);
  for(i=0; i < graph->n; i++) {
      if(vet[i] == -1) {
        printf(YELLOW "(" RESET);
        printf(YELLOW "%d" RESET, i);
        scc(i, vet, graph->n);
        printf(YELLOW");"RESET);
      }
  }
  printf(YELLOW"}"RESET);
}

void stampa_vet(int source, int* vet, upo_dirgraph_t graph){
  int i;
  if(upo_is_graph_empty(graph) == 1){
    printf("\a\"");
    printf(RED "\n\tIl grafo analizzato e' vuoto\n" RESET);
  }
  else if(upo_is_graph_empty(graph) == -1) {
      printf("\a\"");
      printf(RED "\n\tIl grafo analizzato e' nullo\n" RESET);
  }
  else{
    if(source !=-1){
      printf(YELLOW "La radice e' %d\n" RESET,source);
    }
    for(i = 0; i < graph->n; i++) {
      printf(YELLOW "%d |\t" RESET, vet[i]);
    }
  }
}

void print_edg_menu_list() {
  printf(CYAN "\n\t\tMenu archi:\n\t1\tCrea un arco tra due vertici\n\t2\tRimuovi un arco\n\t3\tControlla la presenza di un arco\n\t4\tStampa gli archi uscenti da un dato vertice\n\t5\tStampa gli archi entranti in un dato vertice\n\t6\tStampa gli archi incidenti un dato vertice\n\t0\tTorna al menu precedente\n" RESET);
}

void print_vert_menu_list() {
    printf(CYAN "\n\t\tMenu vertici:\n\t1\tAggiungi un nuovo vertice\n\t2\tRimuovi un vertice\n\t3\tControlla la presenza di un vertice\n\t4\tCalcola il grado entrante di un vertice\n\t5\tCalcola il grado uscente di un vertice\n\t6\tCalcola il grado di un vertice\n\t7\tStampa la lista di adiacenza di un vertice\n\t8\tVerifica se due vertici sono adiacenti\n\t0\tTorna al menu precedente\n" RESET);
}

void print_graph_menu_list() {
    printf(CYAN "\n\t\tMenu grafo:\n\t1\tCrea un grafo vuoto\n\t2\tDistruggi il grafo\n\t3\tControlla se il grafo e' vuoto\n\t4\tVerifica il numero di vertici\n\t5\tVerifica il numero di archi\n\t6\tStampa il grafo\n\t0\tTorna al menu precedente\n" RESET);
}

void print_menu_list() {
    printf(MAGENTA "\n\t\tMenu principale:\n\t1\tOperazioni sul grafo\n\t2\tOperazioni sui vertici\n\t3\tOperazioni sugli archi\n\t4\tProprieta' dei grafi\n\t0\tEsci\n" RESET);
}

void print_graph_proprietis_menu_list() {
    printf(CYAN "\n\t\tMenu proprieta' grafo:\n\t1\tVisita in ampiezza semplice\n\t2\tVisita in profondita' totale\n\t3\tControlla se il grafo contiene cicli\n\t4\tVerifica se il grafo e' un DAG\n\t5\tCalcola un ordinamento topologico\n\t6\tRestituisce le componenti fortemente connesse\n\t0\tTorna al menu precedente\n" RESET);
}

void print_graph(upo_dirgraph_t graph) {
    char* graphToString = upo_print_graph(graph);
    printf(YELLOW "\n\tStampa il grafo\n" RESET);
    printf( YELLOW "\n%s" RESET, graphToString);
    free(graphToString);
}

void strongly_connected_components(upo_dirgraph_t graph) {
    int* vet = upo_strongly_connected_components(graph);
    stampa_scc(vet, graph);
    free(vet);
}

void topological_sort(upo_dirgraph_t graph) {
    int* ord_topologico = upo_topological_sort(graph);
    printf("\n\tOrdinamento Topologico:\n");
    if(ord_topologico != NULL){
        stampa_vet(-1, ord_topologico, graph);
        free(ord_topologico);
    }
    else if(upo_is_graph_empty(graph) == 0){
        printf("\a\"");
        printf(RED"\n\tIl grafo analizzato non e' un DAG\n"RESET);
    }
    else{
        printf("\a\"");
        printf(RED"\n\tIl grafo analizzato e' nullo\n"RESET);
    }
}

void is_DAG(upo_dirgraph_t graph) {
    printf("\n\tVerifica se e' un DAG\n");
    int guess = upo_is_DAG(graph);
    if(guess == 1){
        if(upo_is_graph_empty(graph) == 1) {
            printf("\a\"");
            printf(RED"\n\tIl grafo analizzato e' vuoto\n"RESET);
        }
        else {
            printf(YELLOW"\n\tIl grafo e' un DAG\n"RESET);
        }
    }
    else if(guess == 0) {
        printf(YELLOW"\n\tIl grafo non e' un DAG\n"RESET);
    }
    else {
        printf("\a\"");
        printf(RED "\n\tIl grafo analizzato e' nullo\n" RESET);
    }
}

void is_cyclic(upo_dirgraph_t graph) {
    printf("\n\tVerifica se contiene cicli\n");
    int cycle = upo_cyclic(graph);
    if( cycle== 0){
        if(upo_is_graph_empty(graph) == 1) {
            printf("\a\"");
            printf(RED"\n\tIl grafo analizzato e' vuoto\n"RESET);
        }
        else {
            printf(YELLOW"\n\tIl grafo non contiene cicli\n"RESET);
        }
    }
    else if(cycle == 1){
        printf(YELLOW"\n\tIl grafo contiene cicli\n"RESET);
    }
    else {
        printf("\a\"");
        printf(RED "\n\tIl grafo analizzato e' nullo\n" RESET);
    }
}

void DFS(upo_dirgraph_t graph) {
    printf("\n\tDFS\n");
    int* vet = upo_DFS_tot(graph);
    printf(YELLOW"Vettore dei padri:\n"RESET);
    stampa_vet(-1, vet, graph);
}

void BFS(upo_dirgraph_t graph) {
    printf("\n\tBFS\n");
    int source = 0;
    int* vet;
    printf("\n\tInserire la sorgente: ");
    scanf("%d", &source);
    if(upo_is_graph_empty(graph) == 0) {
        if(source < 0 || source >= (graph)->n){
            printf("\a\"");
            printf(RED"\n\tValore non valido\n"RESET);
            return;
        }
    }
    vet = upo_BFS(graph, source);
    printf(YELLOW"\n\tVettore dei padri:\n"RESET);
    stampa_vet(source, vet, graph);
    free(vet);
}

void inc_edg(upo_dirgraph_t graph) {
    printf("\n\tStampa gli archi incidenti un dato vertice\n");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    upo_list_t incEdg = upo_get_inc_edg(graph, vertex);
    if (incEdg == NULL) {
        if(upo_is_graph_empty(graph) == -1) {
          printf("\a\"");
          printf(RED "\n\tStampa annullata, il grafo e' nullo\n" RESET);
        }
        else {
          printf("\a\"");
          printf(RED "\n\tStampa annullata, il grafo e' vuoto\n" RESET);
        }
    }
    else {
        printf(YELLOW "Vertice: %d;\n" RESET,vertex);
        while (upo_list_size(incEdg) != 0) {
            upo_dir_edge_t nextEdge = upo_remove_first(incEdg);
            printf(YELLOW " %d -> %d;\n" RESET, nextEdge->from, nextEdge->to);
        }
        upo_destroy_list(incEdg);
    }
}

void inc_in_edg(upo_dirgraph_t graph) {
    printf("\n\tStampa gli archi entranti in un dato vertice\n");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    upo_list_t incInEdg = upo_get_inc_in_edg(graph, vertex);
    if (incInEdg == NULL) {
        if(upo_is_graph_empty(graph) == -1) {
          printf("\a\"");
          printf(RED "\n\tStampa annullata, il grafo e' nullo\n" RESET);
        }
        else {
          printf("\a\"");
          printf(RED "\n\tStampa annullata, il grafo e' vuoto\n" RESET);
        }
    }
    else {
        printf(YELLOW "Vertice: %d;\n" RESET,vertex);
        while (upo_list_size(incInEdg) != 0) {
            upo_dir_edge_t nextEdge = upo_remove_first(incInEdg);
            printf(YELLOW " %d -> %d;\n" RESET, nextEdge->from, vertex);
        }
        upo_destroy_list(incInEdg);
    }
}

void inc_out_edg(upo_dirgraph_t graph) {
    printf("\n\tStampa gli archi uscenti da un dato vertice\n");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    upo_list_t incOutEdg = upo_get_inc_out_edg(graph, vertex);
    if (incOutEdg == NULL) {
        if(upo_is_graph_empty(graph) == -1) {
          printf("\a\"");
          printf(RED "\n\tStampa annullata, il grafo e' nullo\n"RESET);
        }
        else {
          printf("\a\"");
          printf(RED"\n\tStampa annullata, il grafo e' vuoto\n"RESET);
        }
    }
    else {
        printf(YELLOW"Vertice: %d;\n"RESET,vertex);
        while (upo_list_size(incOutEdg) != 0) {
            upo_dir_edge_t nextEdge = upo_remove_first(incOutEdg);
            printf(YELLOW" %d -> %d;\n"RESET, vertex, nextEdge->to);
        }
        upo_destroy_list(incOutEdg);
    }
}

void has_edge(upo_dirgraph_t graph) {
    printf("\n\tControlla la presenza di un arco\n");
    int vertex1 = 0;
    int vertex2 = 0;
    printf("\n\tInserire l'indice del vertice da cui parte l'arco: ");
    scanf("%d",&vertex1);
    printf("\n\tInserire l'indice del vertice in cui arriva l'arco: ");
    scanf("%d",&vertex2);
    int returnValue = upo_has_edge(graph, vertex1, vertex2);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tRicerca annullata, il grafo e' nullo\n"RESET);
            break;
        case 0 :
            printf("\a\"");
            printf(RED"\n\tIl grafo non contiene l'arco cercato o almeno uno dei due vertici\n"RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tIl grafo contiene l'arco %d -> %d\n"RESET, vertex1, vertex2);
            break;
    }
}

void remove_edge(upo_dirgraph_t* graph) {
    printf("\n\tRimuovi un arco\n");
    int vertex1 = 0;
    int vertex2 = 0;
    printf("\n\tInserire l'indice del vertice da cui parte l'arco: ");
    scanf("%d",&vertex1);
    printf("\n\tInserire l'indice del vertice in cui arriva l'arco: ");
    scanf("%d",&vertex2);
    int returnValue = upo_remove_edge(*graph, vertex1, vertex2);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tRimozione annullata, il grafo e' nullo\n"RESET);
            break;
        case 0 :
            printf("\a\"");
            printf(RED"\n\tIl grafo non contiene almeno uno dei due vertici oppure non esiste l'arco indicato\n"RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tRimozione dell'arco completata\n"RESET);
            break;
    }
}

void add_edge(upo_dirgraph_t* graph) {
    printf("\n\tCrea un arco tra due vertici\n");
    int vertex1 = 0;
    int vertex2 = 0;
    printf("\n\tInserire l'indice del vertice da cui parte l'arco: ");
    scanf("%d",&vertex1);
    printf("\n\tInserire l'indice del vertice in cui arriva l'arco: ");
    scanf("%d",&vertex2);
    int returnValue = upo_add_edge(*graph, vertex1, vertex2);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tCreazione annullata, il grafo e' nullo\n"RESET);
            break;
        case 0 :
            printf("\a\"");
            printf(RED"\n\tCreazione annullata, almeno uno dei due vertici non esiste oppure l'arco indicato e' gia presente\n"RESET);
            break;
      case 1 :
            printf(YELLOW"\n\tAggiunta completata\n"RESET);
            break;
    }
}

void are_adj(upo_dirgraph_t graph) {
  printf("\n\tVerifica se due vertici sono adiacenti\n");
    int vertex1 = 0;
    int vertex2 = 0;
    printf("\n\tInserire l'indice del primo vertice da controllare: ");
    scanf("%d",&vertex1);
    printf("\n\tInserire l'indice del secondo vertice da controllare: ");
    scanf("%d",&vertex2);
    int returnValue = upo_are_adj(graph, vertex1, vertex2);
    switch (returnValue) {
        case 0 :
            printf("\a\"");
            printf(RED"\n\tI vertici %d e %d non esistono o non sono adiacenti\n"RESET, vertex1, vertex2);
            break;
        case 1 :
            printf(YELLOW"\n\tI vertici %d e %d sono adiacenti\n"RESET, vertex1, vertex2);
            break;
        case -1 :
            printf("\a\"");
            printf(RED"\n\tControllo annullato, il grafo e' nullo\n"RESET);
    }
}

void adj_vert(upo_dirgraph_t graph) {
    printf("\n\tStampa la lista di adiacenza di un vertice\n");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    upo_list_t adjVert = upo_get_adj_vert(graph, vertex);
    if (adjVert == NULL) {
        if(upo_is_graph_empty(graph) == -1) {
          printf("\a\"");
          printf(RED"\n\tCreazione della lista di adiacenza annullata, il grafo e' nullo\n"RESET);
        }
        else if(upo_is_graph_empty(graph) == 1) {
          printf("\a\"");
          printf(RED"\n\tCreazione della lista di adiacenza annullata, il grafo e' vuoto\n"RESET);
        }
        else{
            printf("\a\"");
            printf(RED"\n\tCreazione della lista di adiacenza annullata, il vertice %d non esiste\n"RESET, vertex);
        }
    }
    else {
        printf(YELLOW"\nVertice: %d;\n"RESET,vertex);
        int nextAdjVert = 0;
        int listSize = upo_list_size(adjVert);
        while ( listSize != 0) {
            nextAdjVert = *((int*)upo_remove_first(adjVert));
            printf(YELLOW" %d -> %d;\n"RESET, vertex, nextAdjVert);
            listSize--;
        }
        upo_destroy_list(adjVert);
    }
}

void degree(upo_dirgraph_t graph) {
    printf("\n\tCalcola il grado di un vertice\n");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    int returnValue = upo_get_degree(graph,vertex);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tCalcolo annullato, il grafo e' nullo\n"RESET);
            break;
        default :
        if(upo_has_vertex(graph, vertex) == 1) {
          printf(YELLOW"\n\tIl vertice con indice %d ha grado totale %d\n"RESET,vertex,returnValue);
        }
        else {
          printf("\a\"");
          printf(RED"\n\tIl grafo non contiene il vertice con indice %d\n"RESET,vertex);
        }
        break;
    }
}

void out_degree(upo_dirgraph_t graph) {
    printf("\n\tCalcola il grado uscente di un vertice\n");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    int returnValue = upo_get_out_degree(graph,vertex);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tCalcolo annullato, il grafo e' nullo\n"RESET);
            break;
        default :
        if(upo_has_vertex(graph, vertex) == 1) {
          printf(YELLOW"\n\tIl vertice con indice %d ha grado uscente %d\n"RESET,vertex,returnValue);
        }
        else {
          printf("\a\"");
          printf(RED"\n\tIl grafo non contiene il vertice con indice %d\n"RESET,vertex);
        }
        break;
    }
}

void in_degree(upo_dirgraph_t graph) {
    printf("\n\tCalcola il grado entrante di un vertice\n");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    int returnValue = upo_get_in_degree(graph,vertex);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tCalcolo annullato, il grafo e' nullo\n"RESET);
            break;
        default :
            if(upo_has_vertex(graph, vertex) == 1) {
              printf(YELLOW"\n\tIl vertice con indice %d ha grado entrante %d\n"RESET,vertex,returnValue);
            }
            else {
              printf("\a\"");
              printf(RED"\n\tIl grafo non contiene il vertice con indice %d\n"RESET,vertex);
            }
            break;
    }
}

void has_vertex(upo_dirgraph_t graph) {
    printf("\n\tControlla la presenza di un vertice\n");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da cercare: ");
    scanf("%d",&vertex);
    int returnValue = upo_has_vertex(graph, vertex);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tRicerca annullata, il grafo e' nullo\n"RESET);
            break;
        case 0 :
            printf("\a\"");
            printf(RED"\n\tIl grafo non contiene il vertice con indice %d\n"RESET,vertex);
            break;
        case 1 :
            printf(YELLOW"\n\tIl grafo contiene il vertice con indice %d\n"RESET,vertex);
            break;
    }
}


void remove_vertex(upo_dirgraph_t* graph) {
    printf("\n\tRimuovi un vertice\n");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da rimuovere: ");
    scanf("%d",&vertex);
    int returnValue = upo_remove_vertex(*graph, vertex);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tRimozione annullata, il grafo e' nullo\n"RESET);
            break;
        case 0 :
            printf("\a\"");
            printf(RED"\n\tIl grafo non contiene il vertice con indice %d\n"RESET,vertex);
            break;
        case 1 :
            printf(YELLOW"\n\tRimozione del vertice con indice %d completata\n"RESET,vertex);
            break;
    }
}


void add_vertex(upo_dirgraph_t* graph) {
    printf("\n\tAggiungi un nuovo vertice\n");
    int returnValue = upo_add_vertex(*graph);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tAggiunta annullata, il grafo e' nullo\n"RESET);
            break;
        case 0 :
            printf("\a\"");
            printf(RED"\n\tAggiunta annullata per un errore ignoto\n"RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tAggiunta completata\n"RESET);
            break;
    }
}

void num_edges(upo_dirgraph_t graph) {
    printf("\n\tCalcola il numero di archi\n");
    int returnValue = upo_num_edges(graph);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tIl grafo e' nullo\n"RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tIl grafo contiene %d arco\n"RESET, returnValue);
            break;
        default :
            printf(YELLOW"\n\tIl grafo contiene %d archi\n"RESET,returnValue);
            break;
    }
}

void num_vertices(upo_dirgraph_t graph) {
    printf("\n\tCalcola il numero di vertici\n");
    int returnValue = upo_num_vertices(graph);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tIl grafo e' nullo\n"RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tIl grafo contiene %d vertice\n"RESET, returnValue);
            break;
        default :
            printf(YELLOW"\n\tIl grafo contiene %d vertici\n"RESET,returnValue);
            break;
    }
}

void check_if_empty(upo_dirgraph_t graph) {
    printf("\n\tVerifica lo stato del grafo\n");
    int returnValue = upo_is_graph_empty(graph);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tIl grafo e' nullo\n"RESET);
            break;
        case 0 :
            printf(YELLOW"\n\tIl grafo contiene vertici\n"RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tIl grafo e' vuoto\n"RESET);
            break;
    }
}

void destroy_graph(upo_dirgraph_t* graph) {
    printf("\n\tDistruggi il grafo\n");
    int returnValue = upo_dirgraph_destroy(*graph);
    switch (returnValue) {
        case -1 :
            printf("\a\"");
            printf(RED"\n\tDistruzione annullata, il grafo e' nullo\n"RESET);
            break;
        case 0 :
            printf("\a\"");
            printf(RED"\n\tDistruzione annullata per un errore ignoto\n"RESET);
            break;
        case 1 :
            *graph = NULL;
            printf(YELLOW"\n\tDistruzione completata\n"RESET);
            break;
    }
}

void create_graph(upo_dirgraph_t* graph) {
    printf("\n\tCrea un nuovo grafo\n");
    if (*graph == NULL) {
        *graph = upo_dirgraph_create(0);
        printf(YELLOW"\n\tCreazione completata\n"RESET);
    }
    else {
        printf("\a\"");
        printf(RED"\n\tCreazione annullata, il grafo e' gia stato creato\n"RESET);
    }
}

void graph_properties_operations(upo_dirgraph_t* graph) {
    upo_dirgraph_t* graph_T; /* grafo trasposto */
    int digit = 0;
    while (TRUE) {
        print_graph_proprietis_menu_list();
        selection(&digit);
        switch (digit) {
            case 1 :
                BFS(*graph);
                break;
            case 2 :
                DFS(*graph);
                break;
            case 3 :
                is_cyclic(*graph);
                break;
            case 4 :
                is_DAG(*graph);
                break;
            case 5 :
                  topological_sort(*graph);
                break;
            case 6 :
                strongly_connected_components(*graph);
                break;
            case 0 :
                return;
            default :
                printf("\a\"");
                printf(RED"%d non e' un comando valido\n"RESET,digit);
                break;
        }
    }
}

void edges_operations(upo_dirgraph_t* graph) {
    int digit = 0;
    while (TRUE) {
        print_edg_menu_list();
        selection(&digit);
        switch (digit) {
            case 0 :
                return;
            case 1 :
                add_edge(graph);
                break;
            case 2 :
                remove_edge(graph);
                break;
            case 3 :
                has_edge(*graph);
                break;
            case 4 :
                inc_out_edg(*graph);
                break;
            case 5 :
                inc_in_edg(*graph);
                break;
            case 6 :
                inc_edg(*graph);
                break;
            default :
                printf("\a\"");
                printf(RED"%d non e' un comando valido\n"RESET,digit);
                break;
        }
    }
}

void vertex_operations(upo_dirgraph_t* graph) {
    int digit = 0;
    while (TRUE) {
        print_vert_menu_list();
        selection(&digit);
        switch (digit) {
            case 0 :
                return;
            case 1 :
                add_vertex(graph);
                break;
            case 2 :
                remove_vertex(graph);
                break;
            case 3 :
                has_vertex(*graph);
                break;
            case 4 :
                in_degree(*graph);
                break;
            case 5 :
                out_degree(*graph);
                break;
            case 6 :
                degree(*graph);
                break;
            case 7 :
                adj_vert(*graph);
                break;
            case 8 :
                are_adj(*graph);
                break;
            default :
                printf("\a\"");
                printf(RED"%d non e' un comando valido\n"RESET,digit);
                break;
        }
    }
}

void graph_operations(upo_dirgraph_t* graph) {
    int digit = 0;
    while (TRUE) {
        print_graph_menu_list();
        selection(&digit);
        switch (digit) {

            case 1 :
                create_graph(graph);
                break;
            case 2 :
                destroy_graph(graph);
                break;
            case 3 :
                check_if_empty(*graph);
                break;
            case 4 :
                num_vertices(*graph);
                break;
            case 5 :
                num_edges(*graph);
                break;
            case 6 :
                print_graph(*graph);
                break;
            case 0 :
                return;
            default :
                printf("\a\"");
                printf(RED"%d non e' un comando valido\n"RESET,digit);
                break;
        }
    }
}

int main(void) {
    upo_dirgraph_t graph = NULL;
    int digit = 0;
    while (TRUE) {
        print_menu_list();
        selection(&digit);
        switch (digit){
            case 1 :
                graph_operations(&graph);
                break;
            case 2 :
                vertex_operations(&graph);
                break;
            case 3 :
                edges_operations(&graph);
                break;
            case 4 :
                graph_properties_operations(&graph);
                break;
            case 0 :
                printf("\n\tEsci\n");
                if (graph != NULL) {
                    destroy_graph(&graph);
                    printf("\n");
                }
                return 0;
            default :
                printf("\a\"");
                printf(RED"%d non e' un comando valido\n"RESET,digit);
                break;
        }
    }
}
