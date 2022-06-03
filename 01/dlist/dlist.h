struct Node;
struct List;

struct List *list_new();
void list_delete(struct List *list);

int list_is_empty(struct List const *list);
int list_length(struct List const *list);
struct Node *list_head(struct List const *list);
struct Node *list_tail(struct List const *list);

struct Node *list_prepend(struct List *list, struct Node *node);
struct Node *list_append(struct List *list, struct Node *node);
struct Node *list_insert(struct List *list, struct Node *position, struct Node *node);
void list_remove(struct List *list, struct Node const *node);

struct Node *node_new(char const *s);
void node_delete(struct Node *node);

struct Node *node_next(struct Node const *node);
struct Node *node_prev(struct Node const *node);

char const *node_get(struct Node const *node);
void node_set(struct Node *node, char const *s);
