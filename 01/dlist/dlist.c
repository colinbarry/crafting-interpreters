#include "dlist.h"
#include <stdlib.h>
#include <string.h>

struct Node {
    struct Node *prev, *next;
    char *data;
};

struct List {
    struct Node *head, *tail;
};

struct List *list_new()
{
    struct List *list = malloc(sizeof(*list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_delete(struct List *list)
{
    struct Node *node = list->head;
    while (node)
    {
        struct Node *next = node->next;
        node_delete(node);
        node = next;
    }

    free(list);
}

struct Node *list_head(struct List const *list)
{
    return list->head;
}

struct Node *list_tail(struct List const *list)
{
    return list->tail;
}

struct Node *list_prepend(struct List *list, struct Node *node)
{
    return list_insert(list, list->head, node);
}

struct Node *list_append(struct List *list, struct Node *node)
{
    return list_insert(list, NULL, node);
}

struct Node *list_insert(struct List *list, 
                         struct Node *position,
                         struct Node *node)
{
    if (list->head == position) {
        node->prev = NULL;
        list->head = node;
    } else {
        node->prev = position ? position->prev : list->tail;
        node->prev->next = node;
    }

    if (position == NULL) {
        node->next = NULL;
        list->tail = node;
    } else {
        node->next = position;
        position->prev = node;
    }

    return node;
}

void list_remove(struct List *list, struct Node const *node)
{
    if (list->head == node) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (list->tail == node) {
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }
}

int list_is_empty(struct List const *list)
{
    return list->head == NULL;
}

int list_length(struct List const *list)
{
    int count = 0;
    struct Node const *node = list->head;
    while (node)
    {
        ++count;
        node = node->next;
    }

    return count;
}

struct Node *node_new(char const *s)
{
    struct Node *node = malloc(sizeof (*node));
    node->prev = node->next = NULL;
    node->data = s ? strdup(s) : NULL;
    return node;
}

void node_delete(struct Node *node)
{
    free(node->data);
}

char const *node_get(struct Node const *node)
{
    return node->data;
}

void node_set(struct Node *node, char const *s)
{
    if (node->data)
        free(node->data);

    node->data = s ? strdup(s) : NULL;
}

struct Node *node_next(struct Node const *node)
{
    return node->next;
}

struct Node *node_prev(struct Node const *node)
{
    return node->prev;
    }

