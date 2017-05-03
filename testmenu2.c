#include <stdio.h>
#include "upo_visit.c"
#define TRUE 1
#define FALSE 0

void selection(int* digit) {
    printf("\nScegliere un comando: ");
    scanf("%d", digit);
}

void stampa_vet(int* vet, upo_dirgraph_t graph){
  int i;
  if(upo_is_graph_empty(graph) == 1){
    printf("Il grafo analizzato e' vuoto\n");
  }
  else{
    for(i = 0; i < graph->n; i++) {
      printf("%d |\t", vet[i]);
    }
  }
}

void print_edg_menu_list() {
  printf("\n\t\tMenu archi:\n\t1\tCrea un arco tra due vertici\n\t2\tRimuovi un arco\n\t3\tControlla la presenza di un arco\n\t4\tStampa gli archi uscenti da un dato vertice\n\t5\tStampa gli archi entranti in un dato vertice\n\t6\tStampa gli archi incidenti un dato vertice\n\t0\tTorna al menu precedente\n");
}

void print_vert_menu_list() {
    printf("\n\t\tMenu vertici:\n\t1\tAggiungi un nuovo vertice\n\t2\tRimuovi un vertice\n\t3\tControlla la presenza di un vertice\n\t4\tCalcola il grado entrante di un vertice\n\t5\tCalcola il grado uscente di un vertice\n\t6\tCalcola il grado di un vertice\n\t7\tStampa la lista di adiacenza di un vertice\n\t8\tVerifica se due vertici sono adiacenti\n\t0\tTorna al menu precedente\n");
}

void print_graph_menu_list() {
    printf("\n\t\tMenu grafo:\n\t1\tCrea un grafo vuoto\n\t2\tDistruggi il grafo\n\t3\tControlla se il grafo e' vuoto\n\t4\tVerifica il numero di vertici\n\t5\tVerifica il numero di archi\n\t6\tStampa il grafo\n\t0\tTorna al menu precedente\n");
}

void print_menu_list() {
    printf("\n\t\tMenu principale:\n\t1\tOperazioni sul grafo\n\t2\tOperazioni sui vertici\n\t3\tOperazioni sugli archi\n\t4\tProprieta' dei grafi\n\t0\tEsci\n");
}

void print_graph_proprietis_menu_list() {
    printf("\n\t\tMenu proprieta' grafo:\n\t1\tVisita in ampiezza semplice\n\t2\tVisita in profondita' totale\n\t3\tControlla se il grafo contiene cicli\n\t4\tVerifica se il grafo e' un DAG\n\t5\tCalcola un ordinamento topologico\n\t6\tRestituisce la componente fortemente connessa\n\t0\tTorna al menu precedente\n");
}

void print_graph(upo_dirgraph_t graph) {
    char* graphToString = upo_print_graph(graph);
    printf("\n\tStampa il grafo");
    printf("\n%s", graphToString);
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
          printf("\n\tStampa annullata, il grafo e' nullo.");
        }
        else {
          printf("\n\tStampa annullata, il grafo e' vuoto.");
        }
    }
    else {
        printf("Vertice: %d;\n",vertex);
        while (upo_list_size(incEdg) != 0) {
            upo_dir_edge_t nextEdge = upo_remove_first(incEdg);
            printf(" %d -> %d;\n", nextEdge->from, nextEdge->to);
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
          printf("\n\tStampa annullata, il grafo e' nullo.");
        }
        else {
          printf("\n\tStampa annullata, il grafo e' vuoto.");
        }
    }
    else {
        printf("Vertice: %d;\n",vertex);
        while (upo_list_size(incInEdg) != 0) {
            upo_dir_edge_t nextEdge = upo_remove_first(incInEdg);
            printf(" %d -> %d;\n", nextEdge->from, vertex);
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
          printf("\n\tStampa annullata, il grafo e' nullo.");
        }
        else {
          printf("\n\tStampa annullata, il grafo e' vuoto.");
        }
    }
    else {
        printf("Vertice: %d;\n",vertex);
        while (upo_list_size(incOutEdg) != 0) {
            upo_dir_edge_t nextEdge = upo_remove_first(incOutEdg);
            printf(" %d -> %d;\n", vertex, nextEdge->to);
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
            printf("\n\tRicerca annullata, il grafo e' nullo.");
            break;
        case 0 :
            printf("\n\tIl grafo non contiene l'arco cercato o almeno uno dei due vertici.");
            break;
        case 1 :
            printf("\n\tIl grafo contiene l'arco %d -> %d.", vertex1, vertex2);
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
            printf("\n\tRimozione annullata, il grafo e' nullo."); //o non esiste?
            break;
        case 0 :
            printf("\n\tIl grafo non contiene almeno uno dei due vertici oppure non esiste l'arco indicato.");
            break;
        case 1 :
            printf("\n\tRimozione dell'arco completata.");
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
            printf("\n\tCreazione annullata, il grafo e' nullo.");
            break;
        case 0 :
            printf("\n\tCreazione annullata, almeno uno dei due vertici non esiste oppure l'arco indicato e' gia presente.");
            break;
      case 1 :
            printf("\n\tAggiunta completata.");
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
            printf("\n\tI vertici %d e %d non esistono o non sono adiacenti.");
            break;
        case 1 :
            printf("\n\tI vertici %d e %d sono adiacenti.");
            break;
        case -1 :
            printf("\n\tControllo annullato, il grafo e' nullo.");
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
          printf("\n\tCreazione della lista di adiacenza annullata, il grafo e' nullo.");
        }
        else {
          printf("\n\tCreazione della lista di adiacenza annullata, il grafo e' vuoto.");
        }
    }
    else {
        printf("\nVertice: %d;\n",vertex);
        int nextAdjVert = 0;
        int listSize = upo_list_size(adjVert);
        while ( listSize != 0) {
            nextAdjVert = *((int*)upo_remove_first(adjVert));
            printf(" %d -> %d;\n", vertex, nextAdjVert);
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
            printf("\n\tCalcolo annullato, il grafo e' nullo.");
            break;
        default :
        if(upo_has_vertex(graph, vertex) == 1) {
          printf("\n\tIl vertice con indice %d ha grado totale %d.",vertex,returnValue);
        }
        else {
          printf("\n\tIl grafo non contiene il vertice con indice %d.",vertex);
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
            printf("\n\tCalcolo annullato, il grafo e' nullo.");
            break;
        default :
        if(upo_has_vertex(graph, vertex) == 1) {
          printf("\n\tIl vertice con indice %d ha grado uscente %d.",vertex,returnValue);
        }
        else {
          printf("\n\tIl grafo non contiene il vertice con indice %d.",vertex);
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
            printf("\n\tCalcolo annullato, il grafo e' nullo.");
            break;
        default :
            if(upo_has_vertex(graph, vertex) == 1) {
              printf("\n\tIl vertice con indice %d ha grado entrante %d.",vertex,returnValue);
            }
            else {
              printf("\n\tIl grafo non contiene il vertice con indice %d.",vertex);
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
            printf("\n\tRicerca annullata, il grafo e' nullo.");
            break;
        case 0 :
            printf("\n\tIl grafo non contiene il vertice con indice %d.",vertex);
            break;
        case 1 :
            printf("\n\tIl grafo contiene il vertice con indice %d.",vertex);
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
            printf("\n\tRimozione annullata, il grafo e' nullo.");
            break;
        case 0 :
            printf("\n\tIl grafo non contiene il vertice con indice %d.",vertex);
            break;
        case 1 :
            printf("\n\tRimozione del vertice con indice %d completata.",vertex);
            break;
    }
}


void add_vertex(upo_dirgraph_t* graph) {
    printf("\n\tAggiungi un nuovo vertice");
    int returnValue = upo_add_vertex(*graph);
    switch (returnValue) {
        case -1 :
            printf("\n\tAggiunta annullata, il grafo e' nullo.");
            break;
        case 0 :
            printf("\n\tAggiunta annullata per un errore ignoto.");
            break;
        case 1 :
            printf("\n\tAggiunta completata.");
            break;
    }
}

void num_edges(upo_dirgraph_t graph) {
    int returnValue = upo_num_edges(graph);
    switch (returnValue) {
        case -1 :
            printf("\n\tIl grafo e' nullo");
            break;
        case 1 :
            printf("\n\tIl grafo contiene %d arco", returnValue);
            break;
        default :
            printf("\n\tIl grafo contiene %d archi",returnValue);
            break;
    }
}

void num_vertices(upo_dirgraph_t graph) {
    int returnValue = upo_num_vertices(graph);
    switch (returnValue) {
        case -1 :
            printf("\n\tIl grafo e' nullo");
            break;
        case 1 :
            printf("\n\tIl grafo contiene %d vertice", returnValue);
            break;
        default :
            printf("\n\tIl grafo contiene %d vertici",returnValue);
            break;
    }
}

void check_if_empty(upo_dirgraph_t graph) {
    int returnValue = upo_is_graph_empty(graph);
    switch (returnValue) {
        case -1 :
            printf("\n\tIl grafo e' nullo.");
            break;
        case 0 :
            printf("\n\tIl grafo contiene vertici");
            break;
        case 1 :
            printf("\n\tIl grafo e' vuoto.");
            break;
    }
}

void destroy_graph(upo_dirgraph_t* graph) {
    printf("\n\tDistruggi il grafo");
    int returnValue = upo_dirgraph_destroy(*graph);
    switch (returnValue) {
        case -1 :
            printf("\n\tDistruzione annullata, il grafo e' nullo.");
            break;
        case 0 :
            printf("\n\tDistruzione annullata per un errore ignoto.");
            break;
        case 1 :
            *graph = NULL;
            printf("\n\tDistruzione completata.");
            break;
    }
}

void create_graph(upo_dirgraph_t* graph) {
    printf("\n\tCrea un nuovo grafo");
    if (*graph == NULL) {
        *graph = upo_dirgraph_create(0);
        printf("\n\tCreazione completata.");
    }
    else {
        printf("\n\tCreazione annullata, il grafo e' gia stato creato.");
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
                printf("%d non e' un comando valido.",digit);
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
                printf("%d non e' un comando valido.",digit);
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
                printf("%d non e' un comando valido.",digit);
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
                vet = upo_BFS(*graph, source);
                printf("Vettore dei padri:\n");
                stampa_vet(vet, *graph);
                break;
            case 2 :
                vet = upo_DFS_tot(*graph);
                printf("Vettore dei padri:\n");
                stampa_vet(vet, *graph);
                break;
            case 3 :
                if(upo_cyclic(*graph) == 0){
                  printf("Il grafo non contiene cicli\n");
                }
                else{
                  printf("Il grafo contiene cicli\n");
                }
                break;
            case 4 :
                if(upo_is_DAG(*graph) == 1){
                  printf("Il grafo e' un DAG\n");
                }
                else{
                  printf("Il grafo non e' un DAG\n");
                }
                break;
            case 5 :
                  ord_topologico = upo_topological_sort(*graph);
                  printf("Ordinamento Topologico:\n");
                  stampa_vet(ord_topologico, *graph);
                break;
            case 6 :
                //upo_strongly_connected_components(graph);
                break;
            case 0 :
                return;
            default :
                printf("%c non e' un comando valido.",digit);
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
                printf("%d non e' un comando valido.",digit);
                break;
        }
    }
}
