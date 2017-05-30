
#ifndef UPO_W_DIR_GRAPH_ADJ_MATRIX_H
#define UPO_W_DIR_GRAPH_ADJ_MATRIX_H

#include "upo_w_dir_graph.h"
#include "upo_list.h"




/**
 * @brief Definizione della struttura per rappresentare un grafo con matrice di adiacenza
 */
typedef struct upo_w_dirgraph_s {
    int** adj; /**< Matrice di adiacenza. */
    int n; /**< Numero di nodi del grafo. */
} upo_w_dirgraph_s;

#endif /* UPO_W_DIR_GRAPH_ADJ_MATRIX_H */
