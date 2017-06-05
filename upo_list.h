
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifndef UPO_LIST_H
#define UPO_LIST_H

/**
 * @file upo_list.h
 * @author Luca Piovesan
 * @date 14 Mar 2017
 * @brief Header file for upo_list.
 */

typedef void (*freeFunction)(void *);

/**
 *@brief Nodo della lista
 */
typedef struct upo_list_node {
    void *element; /**< Contenuto del nodo. */
    struct upo_list_node *next; /**< Prossimo elemento. */
} upo_list_node;

/**
 *@brief Lista generica.
 */
struct upo_list_s {
    int logicalLength; /**< Numero di elementi della lista. */
    int elementSize; /**< Dimensione di un elemento (usata per create e destroy). */
    upo_list_node *head; /**< Puntatore al primo nodo della lista. */
    upo_list_node *tail; /**< Puntatore all'ultimo nodo della lista. */
    freeFunction freeFn; /**< Funzione di free del contenuto della lista. */
};

typedef struct upo_list_s* upo_list_t;

/**
 * @brief Tipo iteratore
 */
typedef upo_list_node* upo_iterator;

/**
 * @brief Crea una nuova lista vuota.
 *
 * @param elementSize la dimensione degli elementi contenuti nella lista
 * @param freeFn un puntatore ad una funzione per disallocare gli elementi della lista
 * \return una nuova lista vuota
 */
upo_list_t upo_create_list(int elementSize, freeFunction freeFn);

/**
 * @brief Disalloca una lista
 *
 * @param list la lista
 */
void upo_destroy_list(upo_list_t list);

/**
 * @brief Aggiunge un elemento in testa alla lista
 *
 * @param list la lista
 * @param element l'elemento da aggiungere
 */
void upo_add_first(upo_list_t list, void* element);

/**
 * @brief Aggiunge un elemento in coda alla lista
 *
 * @param list la lista
 * @param element l'elemento da aggiungere
 */
void upo_add_last(upo_list_t list, void *element);

/**
 * @brief Restituisce la dimensione della lista
 *
 * @param list la lista
 * \return il numero di elementi contenuti nella lista
 */
int upo_list_size(upo_list_t list);

/**
 * @brief Restituisce un puntatore al primo elemento della lista
 *
 * @param list la lista
 * \return il primo elemento della lista
 */
void* upo_get_first(upo_list_t list);

/**
 * @brief Restituisce un puntatore all'ultimo elemento della lista
 *
 * @param list la lista
 * \return l'ultimo elemento della lista
 */
void* upo_get_last(upo_list_t list);

/**
 * @brief Restituisce un puntatore all'elemento della lista di indice index
 *
 * @param list la lista
 * @param index l'indice dell'elemento da restituire
 * \return l'elemento della lista di indice index
 */
void* upo_get(upo_list_t list, int index);

/**
 * @brief Rimuove e restituisce un puntatore al primo elemento della lista
 *
 * @param list la lista
 * \return il primo elemento della lista
 */
void* upo_remove_first(upo_list_t list);

/**
 * @brief Rimuove e restituisce un puntatore all'ultimo elemento della lista
 *
 * @param list la lista
 * \return l'ultimo elemento della lista
 */
void* upo_remove_last(upo_list_t list);

/**
 * @brief Rimuove e restituisce un puntatore all'elemento della lista di indice index
 *
 * @param list la lista
 * @param index l'indice dell'elemento da rimuovere
 * \return l'elemento della lista di indice index
 */
void* upo_remove(upo_list_t list, int index);

/**
 * @brief Crea un iteratore della lista
 *
 * @param list la lista
 * \return un iteratore della lista
 */
upo_iterator upo_get_list_iterator(upo_list_t list);

/**
 * @brief Restituisce l'elemento puntato dall'iteratore
 *
 * @param iterator l'iteratore
 * \return l'elemento puntato dall'iteratore
 */
void* upo_get_iterator_element(upo_iterator iterator);

/**
 * @brief Restituisce l'iteratore che punta all'elemento successivo della lista
 *
 * @param iterator l'iteratore
 * \return l'iteratore che punta all'elemento successivo della lista
 */
upo_iterator upo_get_next(upo_iterator iterator);
#endif /* UPO_LIST_H */
