
#ifndef UPO_DIR_GRAPH_ADJ_MATRIX_H
#define UPO_DIR_GRAPH_ADJ_MATRIX_H

#include "upo_dir_graph.h"
#include "upo_list.h"
/**Dovremmo includere "upo_w_dir_graph.h" */



/**
 * @brief Definizione della struttura per rappresentare un grafo con matrice di adiacenza
 */
typedef struct upo_dirgraph_s {
    int** adj; /**< Matrice di adiacenza. */
    int n; /**< Numero di nodi del grafo. */
} upo_dirgraph_s;

#endif /* UPO_DIR_GRAPH_ADJ_MATRIX_H */
