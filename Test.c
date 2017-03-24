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
        printf("Il risultato della add_edge e': %d\n", upo_add_edge(graph, vertex1, vertex2)); // chidere di Inserire i nomi dei vertici e controllarli
      }
    }
  }
  while(scelta != 0)
  // ricordarsi di deallocare il grafo.
}
