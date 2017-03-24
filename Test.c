#include "upo_dir_graph_adj_matrix.c"
#define MAX  4; // totale dei test
void main() {
  int scelta = 0;
  int n = 0;
  upo_dirgraph_t graph = NULL;
  do{
    printf("Questo e' il menu'.\n");
    printf("0 = eliminare il grafo e uscire.\n");
    printf("1 = crea il grafo.\n");
    printf("2 = inserisci un vertice.\n");
    printf("3 = inserisci un arco.\n");
    printf("4 = stampa il grafo.\n");
    scanf("%d", &scelta);
    if(scelta >= 0 && <= MAX){
      if(scelta == 0){
        printf("Il risultato della destroy e': %d\n",upo_dirgraph_destroy(graph));
        fflush(stdout);
      }
      else if(scelta == 1){
        if(upo_dirgraph_destroy(graph) != -1) printf("Distrutto il grafo precedente\n");
        printf("Inserire il numero di nodi del grafo\n", );
        scanf("%d", &n);
        graph = upo_dirgraph_create(n);
      }
      else if(scelta == 2){
        printf("Il risultato della add_vertex e': %d\n",upo_add_vertex(graph));
      }
      else if(scelta == 3){
        printf("Inserire il vertice 1\n",);
        scanf("%d", &vertex1);
        printf("Inserire il vertice 2\n",);
        scanf("%d", &vertex2);
        if(vertex1 >= 0 && vertex1 <= n && vertex2 >= 0 && vertex2 <= n){
        printf("Il risultato della add_edge e': %d\n", upo_add_edge(graph, vertex1, vertex2)); // chidere di Inserire i nomi dei vertici e controllarli
        }
        else{
          printf("ERROR invalid vertex\n");
        }
      }
      else if(scelta == 4){
        char str[DIM]; //dimensione da definire
        str = upo_print_graph(graph);
        printf("Grafo: %s\n", str);
      }
    }
  }
  while(scelta != 0)
  // ricordarsi di deallocare il grafo.
  //per uscire dal ciclo serve il comando 0 che prima dealloca il grafo e poi esce.
}
