#include <stdio.h>
#include "upo_dir_graph_adj_matrix.c"
#include "upo_list.c"
#define TRUE 1
#define FALSE 0

void selection(int* digit) {
    printf("\nScegliere un comando: ");
    scanf("%d", digit);
}

void print_vert_menu_list() {
    printf("\n\t\tMenu vertici:\n\t1\t \n\t2\t \n\t3\t \n\t4\t \n\t5\t \n\t6\t \n\t7\t \n\t8\t \n\t9\t \n\t0\t \n");
}

void print_graph_menu_list() {
    printf("\n\t\tMenu grafo:\n\t1\tCrea un grafo vuoto\n\t2\tDistrugge il grafo\n\t3\tControlla se il grafo è vuoto\n\t4\tVerifica il numero di vertici\n\t5\tVerifica il numero di archi\n\t6\tStampa il grafo\n\t0\tTorna al menu precedente\n");
}

void print_menu_list() {
    printf("\n\t\tMenu principale:\n\t1\tOperazioni sul grafo\n\t2\tOperazioni sui vertici\n\t3\tOperazioni sugli archi\n\t0\tEsci\n");
}

void print_graph(upo_dirgraph_t graph) {
    char* graphToString = upo_print_graph(graph);
    printf("\n\tStampa il grafo");
    printf("\n%s", graphToString);
    free(graphToString);
}

void are_adj(upo_dirgraph_t graph) {
    int vertex1 = 0;
    int vertex2 = 0;
    printf("\n\tInserire l'indice del primo vertice da controllare: ");
    scanf("%d",&vertex1);
    printf("\n\tInserire l'indice del secondo vertice da controllare: ");
    scanf("%d",&vertex2);
    int returnValue = upo_are_adj(graph, vertex1, vertex2);
    switch (returnValue) {
        case 0 :
            printf("\n\tI vertici %d e %d non sono adiacenti.");
            break;
        case 1 :
            printf("\n\tI vertici %d e %d sono adiacenti.");
            break;
        case -1 :
            printf("\n\tControllo annullato, il grafo è nullo.");
    }
}

void adj_vert(upo_dirgraph_t graph) {
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    upo_list_t adjVert = upo_get_adj_vert(graph, vertex);
    if (adjVert == NULL) {
        printf("\n\tCreazione della lista di adiacenza annullata, il grafo è nullo.");
    }
    else {
        printf("Vertice: %d;\n",vertex);
        while (upo_list_size(adj_vert) != 0) {
            int nextAdjVert = *((int*)upo_remove_first(adjVert));
            printf(" %d -> %d;\n", vertex, nextAdjVert);
        }
        upo_destroy_list(adjVert);
    }
}

void degree(upo_dirgraph_t graph) {
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    int returnValue = upo_get_degree(graph,vertex);
    switch (returnValue) {
        case -1 :
            printf("\n\tCalcolo annullato, il grafo è nullo.");
            break;
        default :
            printf("\n\tIl vertice con indice %d ha grado totale %d.",vertex,returnValue);
            break;
    }
}

void out_degree(upo_dirgraph_t graph) {
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    int returnValue = upo_get_out_degree(graph,vertex);
    switch (returnValue) {
        case -1 :
            printf("\n\tCalcolo annullato, il grafo è nullo.");
            break;
        default :
            printf("\n\tIl vertice con indice %d ha grado uscente %d.",vertex,returnValue);
            break;
    }
}

void in_degree(upo_dirgraph_t graph) {
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da controllare: ");
    scanf("%d",&vertex);
    int returnValue = upo_get_in_degree(graph,vertex);
    switch (returnValue) {
        case -1 :
            printf("\n\tCalcolo annullato, il grafo è nullo.");
            break;
        default :
            printf("\n\tIl vertice con indice %d ha grado entrante %d.",vertex,returnValue);
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
            printf("\n\tRicerca annullata, il grafo è nullo."); //o non esiste?
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
    printf("\n\tRimuove un vertice dal grafo");
    int vertex = 0;
    printf("\n\tInserire l'indice del vertice da rimuovere: ");
    scanf("%d",&vertex);
    int returnValue = upo_remove_vertex(*graph, vertex);
    switch (returnValue) {
        case -1 :
            printf("\n\tRimozione annullata, il grafo è nullo."); //o non esiste?
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
            printf("\n\tAggiunta annullata, il grafo è nullo."); //o non esiste?
            break;
        case 0 :
            printf("\n\tAggiunta annullata per un errore ignoto."); //chiedere al professore
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
            printf("\n\tIl grafo è nullo");
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
            printf("\n\tIl grafo è nullo");
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
            printf("\n\tIl grafo è nullo.");
            break;
        case 0 :
            printf("\n\tIl grafo contiene %d vertici",graph->n);
            break;
        case 1 :
            printf("\n\tIl grafo è vuoto.");
            break;
    }
}

void destroy_graph(upo_dirgraph_t* graph) {
    printf("\n\tDistruggi il grafo");
    int returnValue = upo_dirgraph_destroy(*graph);
    switch (returnValue) {
        case -1 :
            printf("\n\tDistruzione annullata, il grafo è nullo."); //o non esiste?
            break;
        case 0 :
            printf("\n\tDistruzione annullata per un errore ignoto."); //chiedere al professore
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
        printf("\n\tCreazione annullata, il grafo è gia stato creato.");
    }
}
/*
void edges_operations(upo_dirgraph_t graph) {
    int digit = 0;
    while (TRUE) {
        selection(&digit);
        switch (digit) {
            case 0 :
                return;
            case 1 :
                add_vertex(graph);
                break;
            case 2 :
                erase_vertex(graph);
                break;
            case 3 :
                has_vertex(graph);
                break;
            case 9 :
                print_edg_menu_list();
                break;
            default :
                printf("%c non è un comando valido.",digit);
                break;
        }
    }
}
*/
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
                printf("%c non è un comando valido.",digit);
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
                printf("%c non è un comando valido.",digit);
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
                //edges_operations(&graph);
                break;
            case 0 :
                printf("\n\tEsci\n");
                if (graph != NULL) {
                    destroy_graph(&graph);
                    printf("\n");
                }
                return 0;
            default :
                printf("%d non è un comando valido.",digit);
                break;
        }
    }
}
