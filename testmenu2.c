#include <stdio.h>
#include "upo_visit.c"
#define TRUE 1
#define FALSE 0
#define RED "\033[31;1m" /**stampa errori*/
#define YELLOW "\033[33;1m" /**stampe risultati*/
#define MAGENTA "\033[35;1m" /**stampa sottomenu*/
#define CYAN "\033[36;1m" /**stampa primo menu*/
#define RESET "\033[0m" /**valore di default delle stampe*/

void selection(int* digit) {
    printf("\nScegliere un comando: ");
    scanf("%d", digit);
}

void scc(int padre, int* vet, int dim){
  int i;
  for(i = 0; i < dim; i++){
    if(vet[i] == padre){
      printf(YELLOW "%d |\t" RESET, i);
      scc(i, vet, dim);
    }
  }
  return;
}

void stampa_scc(int* vet, upo_dirgraph_t graph) {
  if(vet == NULL) {
      if(upo_is_graph_empty(graph)==-1) {
          printf(RED "Il grafo non esiste\n" RESET);
      }
      else if(upo_is_graph_empty(graph)==1) {
          printf(RED "Il grafo e' vuoto\n" RESET);
      }
  }
  int i;
  for(i=0; i < graph->n; i++) {
      if(vet[i] == -1) {
        printf(YELLOW "Parte fortemente connessa\n" RESET);
        printf(YELLOW "%d |\t" RESET, i);
        scc(i, vet, graph->n);
        printf("\n");
      }
  }
}

void stampa_vet(int source, int* vet, upo_dirgraph_t graph){
  int i;
  if(upo_is_graph_empty(graph) == 1){
    printf(RED "Il grafo analizzato e' vuoto\n" RESET);
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
    printf(CYAN "\n\t\tMenu proprieta' grafo:\n\t1\tVisita in ampiezza semplice\n\t2\tVisita in profondita' totale\n\t3\tControlla se il grafo contiene cicli\n\t4\tVerifica se il grafo e' un DAG\n\t5\tCalcola un ordinamento topologico\n\t6\tRestituisce la componente fortemente connessa\n\t0\tTorna al menu precedente\n" RESET);
}

void print_graph(upo_dirgraph_t graph) {
    char* graphToString = upo_print_graph(graph);
    printf(YELLOW "\n\tStampa il grafo" RESET);
    printf( YELLOW "\n%s" RESET, graphToString);
    free(graphToString);
}

void inc_edg(upo_dirgraph_t graph) {
    printf("\n\tStampa gli archi incidenti un dato vertice");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    upo_list_t incEdg = upo_get_inc_edg(graph, vertex);
    if (incEdg == NULL) {
        if(upo_is_graph_empty(graph) == -1) {
          printf(RED "\n\tStampa annullata, il grafo e' nullo." RESET);
        }
        else {
          printf(RED "\n\tStampa annullata, il grafo e' vuoto." RESET);
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
    printf("\n\tStampa gli archi entranti in un dato vertice");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    upo_list_t incInEdg = upo_get_inc_in_edg(graph, vertex);
    if (incInEdg == NULL) {
        if(upo_is_graph_empty(graph) == -1) {
          printf(RED "\n\tStampa annullata, il grafo e' nullo." RESET);
        }
        else {
          printf(RED "\n\tStampa annullata, il grafo e' vuoto." RESET);
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
    printf("\n\tStampa gli archi uscenti da un dato vertice");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    upo_list_t incOutEdg = upo_get_inc_out_edg(graph, vertex);
    if (incOutEdg == NULL) {
        if(upo_is_graph_empty(graph) == -1) {
          printf(RED "\n\tStampa annullata, il grafo e' nullo."RESET);
        }
        else {
          printf(RED"\n\tStampa annullata, il grafo e' vuoto."RESET);
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
    printf("\n\tControlla la presenza di un arco");
    int vertex1 = 0;
    int vertex2 = 0;
    printf("\n\tInserire l'indice del vertice da cui parte l'arco: ");
    scanf("%d",&vertex1);
    printf("\n\tInserire l'indice del vertice in cui arriva l'arco: ");
    scanf("%d",&vertex2);
    int returnValue = upo_has_edge(graph, vertex1, vertex2);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tRicerca annullata, il grafo e' nullo."RESET);
            break;
        case 0 :
            printf(RED"\n\tIl grafo non contiene l'arco cercato o almeno uno dei due vertici."RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tIl grafo contiene l'arco %d -> %d."RESET, vertex1, vertex2);
            break;
    }
}

void remove_edge(upo_dirgraph_t* graph) {
    printf("\n\tRimuovi un arco");
    int vertex1 = 0;
    int vertex2 = 0;
    printf("\n\tInserire l'indice del vertice da cui parte l'arco: ");
    scanf("%d",&vertex1);
    printf("\n\tInserire l'indice del vertice in cui arriva l'arco: ");
    scanf("%d",&vertex2);
    int returnValue = upo_remove_edge(*graph, vertex1, vertex2);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tRimozione annullata, il grafo e' nullo."RESET); //o non esiste?
            break;
        case 0 :
            printf(RED"\n\tIl grafo non contiene almeno uno dei due vertici oppure non esiste l'arco indicato."RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tRimozione dell'arco completata."RESET);
            break;
    }
}

void add_edge(upo_dirgraph_t* graph) {
    printf("\n\tCrea un arco tra due vertici");
    int vertex1 = 0;
    int vertex2 = 0;
    printf("\n\tInserire l'indice del vertice da cui parte l'arco: ");
    scanf("%d",&vertex1);
    printf("\n\tInserire l'indice del vertice in cui arriva l'arco: ");
    scanf("%d",&vertex2);
    int returnValue = upo_add_edge(*graph, vertex1, vertex2);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tCreazione annullata, il grafo e' nullo."RESET);
            break;
        case 0 :
            printf(RED"\n\tCreazione annullata, almeno uno dei due vertici non esiste oppure l'arco indicato e' gia presente."RESET);
            break;
      case 1 :
            printf(YELLOW"\n\tAggiunta completata."RESET);
            break;
    }
}

void are_adj(upo_dirgraph_t graph) {
  printf("\n\tVerifica se due vertici sono adiacenti");
    int vertex1 = 0;
    int vertex2 = 0;
    printf("\n\tInserire l'indice del primo vertice da controllare: ");
    scanf("%d",&vertex1);
    printf("\n\tInserire l'indice del secondo vertice da controllare: ");
    scanf("%d",&vertex2);
    int returnValue = upo_are_adj(graph, vertex1, vertex2);
    switch (returnValue) {
        case 0 :
            printf(RED"\n\tI vertici %d e %d non esistono o non sono adiacenti."RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tI vertici %d e %d sono adiacenti."RESET);
            break;
        case -1 :
            printf(RED"\n\tControllo annullato, il grafo e' nullo."RESET);
    }
}

void adj_vert(upo_dirgraph_t graph) {
    printf("\n\tStampa la lista di adiacenza di un vertice");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    upo_list_t adjVert = upo_get_adj_vert(graph, vertex);
    if (adjVert == NULL) {
        if(upo_is_graph_empty(graph) == -1) {
          printf(RED"\n\tCreazione della lista di adiacenza annullata, il grafo e' nullo."RESET);
        }
        else {
          printf(RED"\n\tCreazione della lista di adiacenza annullata, il grafo e' vuoto."RESET);
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
    printf("\n\tCalcola il grado di un vertice");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    int returnValue = upo_get_degree(graph,vertex);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tCalcolo annullato, il grafo e' nullo."RESET);
            break;
        default :
        if(upo_has_vertex(graph, vertex) == 1) {
          printf(YELLOW"\n\tIl vertice con indice %d ha grado totale %d."RESET,vertex,returnValue);
        }
        else {
          printf(RED"\n\tIl grafo non contiene il vertice con indice %d."RESET,vertex);
        }
        break;
    }
}

void out_degree(upo_dirgraph_t graph) {
    printf("\n\tCalcola il grado uscente di un vertice");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    int returnValue = upo_get_out_degree(graph,vertex);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tCalcolo annullato, il grafo e' nullo."RESET);
            break;
        default :
        if(upo_has_vertex(graph, vertex) == 1) {
          printf(YELLOW"\n\tIl vertice con indice %d ha grado uscente %d."RESET,vertex,returnValue);
        }
        else {
          printf(RED"\n\tIl grafo non contiene il vertice con indice %d."RESET,vertex);
        }
        break;
    }
}

void in_degree(upo_dirgraph_t graph) {
    printf("\n\tCalcola il grado entrante di un vertice");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    int returnValue = upo_get_in_degree(graph,vertex);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tCalcolo annullato, il grafo e' nullo."RESET);
            break;
        default :
            if(upo_has_vertex(graph, vertex) == 1) {
              printf(YELLOW"\n\tIl vertice con indice %d ha grado entrante %d."RESET,vertex,returnValue);
            }
            else {
              printf(RED"\n\tIl grafo non contiene il vertice con indice %d."RESET,vertex);
            }
            break;
    }
}

void has_vertex(upo_dirgraph_t graph) {
    printf("\n\tControlla la presenza di un vertice");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da cercare: ");
    scanf("%d",&vertex);
    int returnValue = upo_has_vertex(graph, vertex);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tRicerca annullata, il grafo e' nullo."RESET);
            break;
        case 0 :
            printf(RED"\n\tIl grafo non contiene il vertice con indice %d."RESET,vertex);
            break;
        case 1 :
            printf(YELLOW"\n\tIl grafo contiene il vertice con indice %d."RESET,vertex);
            break;
    }
}


void remove_vertex(upo_dirgraph_t* graph) {
    printf("\n\tRimuovi un vertice");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da rimuovere: ");
    scanf("%d",&vertex);
    int returnValue = upo_remove_vertex(*graph, vertex);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tRimozione annullata, il grafo e' nullo."RESET);
            break;
        case 0 :
            printf(RED"\n\tIl grafo non contiene il vertice con indice %d."RESET,vertex);
            break;
        case 1 :
            printf(YELLOW"\n\tRimozione del vertice con indice %d completata."RESET,vertex);
            break;
    }
}


void add_vertex(upo_dirgraph_t* graph) {
    printf("\n\tAggiungi un nuovo vertice");
    int returnValue = upo_add_vertex(*graph);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tAggiunta annullata, il grafo e' nullo."RESET);
            break;
        case 0 :
            printf(RED"\n\tAggiunta annullata per un errore ignoto."RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tAggiunta completata."RESET);
            break;
    }
}

void num_edges(upo_dirgraph_t graph) {
    int returnValue = upo_num_edges(graph);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tIl grafo e' nullo"RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tIl grafo contiene %d arco"RESET, returnValue);
            break;
        default :
            printf(YELLOW"\n\tIl grafo contiene %d archi"RESET,returnValue);
            break;
    }
}

void num_vertices(upo_dirgraph_t graph) {
    int returnValue = upo_num_vertices(graph);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tIl grafo e' nullo"RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tIl grafo contiene %d vertice"RESET, returnValue);
            break;
        default :
            printf(YELLOW"\n\tIl grafo contiene %d vertici"RESET,returnValue);
            break;
    }
}

void check_if_empty(upo_dirgraph_t graph) {
    int returnValue = upo_is_graph_empty(graph);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tIl grafo e' nullo."RESET);
            break;
        case 0 :
            printf(YELLOW"\n\tIl grafo contiene vertici"RESET);
            break;
        case 1 :
            printf(YELLOW"\n\tIl grafo e' vuoto."RESET);
            break;
    }
}

void destroy_graph(upo_dirgraph_t* graph) {
    printf("\n\tDistruggi il grafo");
    int returnValue = upo_dirgraph_destroy(*graph);
    switch (returnValue) {
        case -1 :
            printf(RED"\n\tDistruzione annullata, il grafo e' nullo."RESET);
            break;
        case 0 :
            printf(RED"\n\tDistruzione annullata per un errore ignoto."RESET);
            break;
        case 1 :
            *graph = NULL;
            printf(YELLOW"\n\tDistruzione completata."RESET);
            break;
    }
}

void create_graph(upo_dirgraph_t* graph) {
    printf("\n\tCrea un nuovo grafo");
    if (*graph == NULL) {
        *graph = upo_dirgraph_create(0);
        printf(YELLOW"\n\tCreazione completata."RESET);
    }
    else {
        printf(RED"\n\tCreazione annullata, il grafo e' gia stato creato."RESET);
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
                printf(RED"%d non e' un comando valido."RESET,digit);
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
                printf(RED"%d non e' un comando valido."RESET,digit);
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
                printf(RED"%d non e' un comando valido."RESET,digit);
                break;
        }
    }
}

void graph_proprietis_operations(upo_dirgraph_t* graph) {
    upo_dirgraph_t* graph_T; /* grafo trasposto */
    int digit = 0;
    int source = 0;
    int* vet;
    int* ord_topologico;
    while (TRUE) {
        print_graph_proprietis_menu_list();
        selection(&digit);
        switch (digit) {
            case 1 :
                printf("Inserire la sorgente\n");
                scanf("%d", &source);
                if(source < 0 || source >= (*graph)->n){
                    printf(RED"Valore non valido\n"RESET);
                    break;
                }
                vet = upo_BFS(*graph, source);
                printf(YELLOW"Vettore dei padri:\n"RESET);
                stampa_vet(source, vet, *graph);
                break;
            case 2 :
                vet = upo_DFS_tot(*graph);
                printf(YELLOW"Vettore dei padri:\n"RESET);
                stampa_vet(-1, vet, *graph);
                break;
            case 3 :
                if(upo_cyclic(*graph) == 0){
                  printf(YELLOW"Il grafo non contiene cicli\n"RESET);
                }
                else{
                  printf(YELLOW"Il grafo contiene cicli\n"RESET);
                }
                break;
            case 4 :
                if(upo_is_DAG(*graph) == 1){
                  printf(YELLOW"Il grafo e' un DAG\n"RESET);
                }
                else{
                  printf(YELLOW"Il grafo non e' un DAG\n"RESET);
                }
                break;
            case 5 :
                  ord_topologico = upo_topological_sort(*graph);
                  printf("Ordinamento Topologico:\n");
                  if(ord_topologico != NULL){
                    stampa_vet(-1, ord_topologico, *graph);
                  }
                  else{
                    printf(RED"Il grafo analizzato non e' un DAG\n"RESET);
                  }
                break;
            case 6 :
                vet = upo_strongly_connected_components(*graph);
                stampa_scc(vet, *graph);
                break;
            case 0 :
                return;
            default :
                printf(RED"%c non e' un comando valido."RESET,digit);
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
                graph_proprietis_operations(&graph);
                break;
            case 0 :
                printf("\n\tEsci\n");
                if (graph != NULL) {
                    destroy_graph(&graph);
                    printf("\n");
                }
                return 0;
            default :
                printf(RED"%d non e' un comando valido."RESET,digit);
                break;
        }
    }
}
