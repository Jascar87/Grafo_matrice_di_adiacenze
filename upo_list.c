#include "upo_list.h"

upo_list_t upo_create_list(int elementSize, freeFunction freeFn) {
    upo_list_t list = malloc(sizeof (struct upo_list_s));
    assert(elementSize > 0);
    list->logicalLength = 0;
    list->elementSize = elementSize;
    list->head = list->tail = NULL;
    list->freeFn = freeFn;
    return list;
}

void upo_destroy_list(upo_list_t list) {
    if(list==NULL) return;
    upo_list_node *current;
    while (list->head != NULL) {
        current = list->head;
        list->head = current->next;

        if (list->freeFn) {
            list->freeFn(current->element);
        }
        else
            free(current->element);
        free(current);
    }
    free(list);
}

void upo_add_first(upo_list_t list, void *element) {
    upo_list_node *node = malloc(sizeof (upo_list_node));
    node->element = element;

    node->next = list->head;
    list->head = node;

    // first node?
    if (!list->tail) {
        list->tail = list->head;
    }

    list->logicalLength++;
}

void upo_add_last(upo_list_t list, void *element) {
    upo_list_node *node = malloc(sizeof (upo_list_node));
    node->element = element;
    node->next = NULL;

    if (list->logicalLength == 0) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->logicalLength++;
}

void* upo_get_first(upo_list_t list) {
    assert(list->head != NULL);

    upo_list_node *node = list->head;
    return node->element;

}

void* upo_get_last(upo_list_t list) {
    assert(list->tail != NULL);
    upo_list_node *node = list->tail;
    return node->element;
}

void* upo_get(upo_list_t list, int index) {
    assert(list->tail != NULL);
    upo_list_node *node = list->head;
    int i;
    for (i = 0; i < index; i++) {
        node = node->next;
    }
    return node->element;
}

int upo_list_size(upo_list_t list) {
    return list->logicalLength;
}

void* upo_remove_first(upo_list_t list) {
    if (list->logicalLength == 0) return NULL;
    upo_list_node* node = list->head;
    void* element = node->element;
    list->head = node->next;
    free(node->element);
    free(node);
    list->logicalLength--;
    return element;
}

void* upo_remove_last(upo_list_t list) {
    if (list->logicalLength == 0) return NULL;
    if (list->logicalLength == 1) {
        return upo_remove_first(list);
    }
    upo_list_node* prev = list->head;
    upo_list_node* node = prev->next;
    while (node->next != NULL) {
        node = node->next;
        prev = prev->next;
    }
    void* element = node->element;
    prev->next = NULL;
    list->tail = prev;
    free(node);
    list->logicalLength--;
    return element;
}

void* upo_remove(upo_list_t list, int index) {
    if (list->logicalLength == 0 || list->logicalLength <= index) return NULL;
    if (list->logicalLength == 1 || index==0) {
        return upo_remove_first(list);
    }
    if(index == upo_list_size(list)-1) {
        return upo_remove_last(list);
    }
    upo_list_node* prev = list->head;
    upo_list_node* node = prev->next;
    int i=1;
    while (i<index) {
        node = node->next;
        prev = prev->next;
        i++;
    }
    void* element = node->element;
    prev->next = node->next;
    free(node);
    list->logicalLength--;
    return element;
}

upo_iterator upo_get_list_iterator(upo_list_t list) {
    return (upo_iterator) list->head;
}
void* upo_get_iterator_element(upo_iterator iterator) {
    return iterator->element;
}
upo_iterator upo_get_next(upo_iterator iterator) {
    return (upo_iterator) iterator->next;
}
