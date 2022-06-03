#include "dlist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRINGIFY_INNER(X) #X
#define STRINGIFY(X) STRINGIFY_INNER(X)
#define EXPECT(expr) if (!(expr)) { puts("FAIL: " __FILE__ ":" STRINGIFY(__LINE__) " | " # expr); }

static int node_eq(struct Node const *node, char const *data)
{
    return strcmp(node_get(node), data) == 0;
}

static void a_new_list_is_empty()
{
    struct List* list = list_new();
    EXPECT(list_head(list) == NULL);
    EXPECT(list_tail(list) == NULL);
    list_delete(list);
}

static void can_prepend()
{
    struct List* list = list_new();
    struct Node const* alfa, *bravo, *charlie;

    alfa = list_prepend(list, node_new("alfa"));
    EXPECT(list_head(list) == alfa);
    EXPECT(list_tail(list) == alfa);
    EXPECT(node_eq(alfa, "alfa"));
    EXPECT(node_next(alfa) == NULL);
    EXPECT(node_prev(alfa) == NULL);

    bravo = list_prepend(list, node_new("bravo"));
    EXPECT(list_head(list) == bravo);
    EXPECT(list_tail(list) == alfa);
    EXPECT(node_eq(bravo, "bravo"));
    EXPECT(node_next(alfa) == NULL);
    EXPECT(node_prev(alfa) == bravo);
    EXPECT(node_next(bravo) == alfa);
    EXPECT(node_prev(bravo) == NULL);

    charlie = list_prepend(list, node_new("charlie"));
    EXPECT(list_head(list) == charlie);
    EXPECT(list_tail(list) == alfa);
    EXPECT(node_eq(charlie, "charlie"));
    EXPECT(node_next(alfa) == NULL);
    EXPECT(node_prev(alfa) == bravo);
    EXPECT(node_next(bravo) == alfa);
    EXPECT(node_prev(bravo) == charlie);
    EXPECT(node_next(charlie) == bravo);
    EXPECT(node_prev(charlie) == NULL);

    list_delete(list);
}

static void can_insert()
{
    struct List *list = list_new();
    struct Node *alfa, *bravo, *charlie;

    alfa = list_insert(list, NULL, node_new("alfa"));
    EXPECT(node_eq(alfa, "alfa"));
    EXPECT(list_head(list) == alfa);
    EXPECT(list_tail(list) == alfa);
    EXPECT(node_next(alfa) == NULL);
    EXPECT(node_prev(alfa) == NULL);

    bravo = list_insert(list, alfa, node_new("bravo"));
    EXPECT(node_eq(bravo, "bravo"));
    EXPECT(list_head(list) == bravo);
    EXPECT(list_tail(list) == alfa);
    EXPECT(node_next(alfa) == NULL);
    EXPECT(node_prev(alfa) == bravo);
    EXPECT(node_next(bravo) == alfa);
    EXPECT(node_prev(bravo) == NULL);

    charlie = list_insert(list, alfa, node_new("charlie"));
    EXPECT(node_eq(charlie, "charlie"));
    EXPECT(list_head(list) == bravo);
    EXPECT(list_tail(list) == alfa);
    EXPECT(node_next(alfa) == NULL);
    EXPECT(node_prev(alfa) == charlie);
    EXPECT(node_next(bravo) == charlie);
    EXPECT(node_prev(bravo) == NULL);
    EXPECT(node_next(charlie) == alfa);
    EXPECT(node_prev(charlie) == bravo);

    list_delete(list);
}

static void can_append()
{
    struct List* list = list_new();
    struct Node const* alfa, *bravo, *charlie;

    alfa = list_append(list, node_new("alfa"));
    EXPECT(list_head(list) == alfa);
    EXPECT(list_tail(list) == alfa);
    EXPECT(node_eq(alfa, "alfa"));
    EXPECT(node_next(alfa) == NULL);
    EXPECT(node_prev(alfa) == NULL);

    bravo = list_append(list, node_new("bravo"));
    EXPECT(list_head(list) == alfa);
    EXPECT(list_tail(list) == bravo);
    EXPECT(node_eq(bravo, "bravo"));
    EXPECT(node_next(alfa) == bravo);
    EXPECT(node_prev(alfa) == NULL);
    EXPECT(node_next(bravo) == NULL);
    EXPECT(node_prev(bravo) == alfa);

    charlie = list_append(list, node_new("charlie"));
    EXPECT(list_head(list) == alfa);
    EXPECT(list_tail(list) == charlie);
    EXPECT(node_eq(charlie, "charlie"));
    EXPECT(node_next(alfa) == bravo);
    EXPECT(node_prev(alfa) == NULL);
    EXPECT(node_next(bravo) == charlie);
    EXPECT(node_prev(bravo) == alfa);
    EXPECT(node_next(charlie) == NULL);
    EXPECT(node_prev(charlie) == bravo);

    list_delete(list);
}


static void can_remove()
{
    struct List* list = list_new();
    struct Node* alfa, *bravo, *charlie;

    alfa = list_append(list, node_new("alfa"));
    bravo = list_append(list, node_new("bravo"));
    charlie = list_append(list, node_new("charlie"));

    list_remove(list, bravo);
    node_delete(bravo);
    EXPECT(list_head(list) == alfa);
    EXPECT(node_next(alfa) == charlie);
    EXPECT(node_next(charlie) == NULL);

    list_remove(list, alfa);
    node_delete(alfa);
    EXPECT(list_head(list) == charlie);
    EXPECT(node_next(charlie) == NULL);

    list_remove(list, charlie);
    node_delete(charlie);
    EXPECT(list_head(list) == NULL);

    list_delete(list);
}


static void can_query_emptiness()
{
    struct List* list = list_new();
    struct Node* node;

    EXPECT(list_is_empty(list));

    node = list_append(list, node_new("alfa"));
    EXPECT(!list_is_empty(list));

    list_remove(list, node);
    node_delete(node);
    EXPECT(list_is_empty(list));

    list_delete(list);
}

static void can_query_length()
{
    struct List* list = list_new();
    struct Node* alfa, *bravo, *charlie;

    EXPECT(list_length(list) == 0);

    alfa = list_append(list, node_new("alfa"));
    EXPECT(list_length(list) == 1);

    bravo = list_append(list, node_new("bravo"));
    EXPECT(list_length(list) == 2);

    charlie = list_append(list, node_new("charlie"));
    EXPECT(list_length(list) == 3);

    list_remove(list, bravo);
    node_delete(bravo);
    EXPECT(list_length(list) == 2);

    list_remove(list, alfa);
    node_delete(alfa);
    EXPECT(list_length(list) == 1);

    list_remove(list, charlie);
    node_delete(charlie);
    EXPECT(list_length(list) == 0);

    list_delete(list);
}

void can_change_node_data()
{
    struct List* list = list_new();
    struct Node* node;

    node = list_append(list, node_new("alfa"));
    EXPECT(strcmp(node_get(node), "alfa") == 0);

    node_set(node, "bravo");
    EXPECT(strcmp(node_get(node), "bravo") == 0);

    list_delete(list);
}

int main(int argc, char *argv[])
{
    a_new_list_is_empty();
    can_prepend();
    can_insert();
    can_append();
    can_remove();
    can_query_emptiness();
    can_query_length();
    can_change_node_data();

    return EXIT_SUCCESS;
}

