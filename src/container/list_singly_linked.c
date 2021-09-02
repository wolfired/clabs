#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "container/list_singly_linked.h"

typedef struct _Node {
    void*         value;
    struct _Node* next;
} Node_, *Node;

typedef struct _Meta {
    Count count;
} Meta_, *Meta;

typedef bool (*NodeIterator)(Index index, Node node, void* voidargs);

static void node_iteration(Node node, NodeIterator iterator, void* voidargs) {
    for(Index index = -1; NULL != node && iterator(++index, node, voidargs); node = node->next) {}
}

typedef struct {
    Index index_need;
    Node  node_need;
} node_at_node_iter_args;

static bool node_at_node_iter(Index index, Node node, void* voidargs) {
    node_at_node_iter_args* args = (node_at_node_iter_args*)voidargs;

    if(index == args->index_need) {
        args->node_need = node;
    }

    return 0 < args->index_need && index < args->index_need;
}

static Node node_at(Node node, Index index) {
    node_at_node_iter_args args = {index, NULL};
    node_iteration(node, node_at_node_iter, &args);
    return args.node_need;
}

static Value value_at(Node node, Index index) {
    node = node_at(node, index);
    return NULL == node || NULL == node->next ? NULL : node->next->value;
}

typedef struct {
    Value value_need;
    Index index_need;
    Node  node_need;
} node_of_node_iter_args;

static bool node_of_node_iter(Index index, Node node, void* voidargs) {
    node_of_node_iter_args* args = (node_of_node_iter_args*)voidargs;

    if(NULL != node->next && node->next->value == args->value_need) {
        args->index_need = index;
        args->node_need  = node;
        return false;
    }

    return true;
}

static Node node_of(Node node, Value value) {
    node_of_node_iter_args args = {value, -1, NULL};
    node_iteration(node, node_of_node_iter, &args);
    return args.node_need;
}

static Index index_of(Node node, Value value) {
    node_of_node_iter_args args = {value, -1, NULL};
    node_iteration(node, node_of_node_iter, &args);
    return args.index_need;
}

static Node node_create(Value value, Node next) {
    Node node = (Node)malloc(sizeof(Node_));

    node->value = value;
    node->next  = next;

    return node;
}

static void node_insert_node(Node node, Node newnode) {
    newnode->next = node->next;
    node->next    = newnode;
}

static bool node_insert_value(Node node, Value value) {
    if(NULL == node) { return false; }
    node_insert_node(node, node_create(value, node->next));
    return true;
}

static Node node_remove(Node node) {
    if(NULL == node || NULL == node->next) { return NULL; }
    Node next  = node->next;
    node->next = next->next;
    return next;
}

static bool node_delete(Node node, Value* p_retval) {
    Node next = node_remove(node);
    if(NULL == next) { return false; }
    if(NULL != p_retval) { *p_retval = next->value; }
    free(next);
    return true;
}

static Value node_update(Node node, Value newval) {
    if(NULL == node || NULL == node->next) { return NULL; }
    Value oldval      = node->next->value;
    node->next->value = newval;
    return oldval;
}

static Node root_create() {
    Node root = node_create((Value)malloc(sizeof(Meta_)), NULL);

    ((Meta)root->value)->count = 0;

    return root;
}

static void root_delete(Node root) {
    free(root->value);
    free(root);
}

static inline void count_inc(Node node) {
    ((Meta)node->value)->count += 1;
}

static inline void count_dec(Node node) {
    ((Meta)node->value)->count -= 1;
}

void list_create(List* p_list) {
    *p_list = (List)root_create();
}

void list_delete(List* p_list) {
    while(node_delete((Node)*p_list, NULL)) {}
    root_delete((Node)*p_list);
    *p_list = NULL;
}

Count list_count(List list) {
    return ((Meta)((Node)list)->value)->count;
}

Count list_count_set(List list, Count count) {
    while(node_delete(node_at((Node)list, count), NULL)) { count_dec((Node)list); }
    return list_count(list);
}

/**
 * @brief
 *
 * @param list
 * @param index -count-1 <= i <= count
 * @param value
 * @return Count
 */
Count list_insert(List list, Index index, Value value) {
    index = 0 > index ? list_count(list) + 1 + index : index;
    if(node_insert_value(node_at((Node)list, index), value)) { count_inc((Node)list); }
    return list_count(list);
}

/**
 * @brief 
 * 
 * @param list 
 * @param index -count <= i <= count-1
 * @param p_retval 
 * @return Count 
 */
Count list_remove(List list, Index index, Value* p_retval) {
    index = 0 > index ? list_count(list) + index : index;
    if(node_delete(node_at((Node)list, index), p_retval)) { count_dec((Node)list); }
    return list_count(list);
}

/**
 * @brief 
 * 
 * @param list 
 * @param index -count <= i <= count-1
 * @param newval 
 * @return Value 
 */
Value list_update(List list, Index index, Value newval) {
    index = 0 > index ? list_count(list) + index : index;
    return node_update(node_at((Node)list, index), newval);
}

/**
 * @brief 
 * 
 * @param list 
 * @param i -count <= i <= count-1
 * @param j -count <= i <= count-1
 */
void list_swap(List list, Index i, Index j) {
    i = 0 > i ? list_count(list) + i : i;
    j = 0 > j ? list_count(list) + j : j;

    if(i == j) { return; }

    Node node_i = node_at((Node)list, i);
    if(NULL == node_i || NULL == node_i->next) { return; }

    Node node_j = node_at((Node)list, j);
    if(NULL == node_j || NULL == node_j->next) { return; }

    node_i->next->value = (Value)((uintptr_t)node_i->next->value ^ (uintptr_t)node_j->next->value);
    node_j->next->value = (Value)((uintptr_t)node_i->next->value ^ (uintptr_t)node_j->next->value);
    node_i->next->value = (Value)((uintptr_t)node_i->next->value ^ (uintptr_t)node_j->next->value);
}

/**
 * @brief 
 * 
 * @param list 
 * @param f -count <= f <= count-1
 * @param t -count <= t <= count-1
 */
void list_move(List list, Index f, Index t) {
    f = 0 > f ? list_count(list) + f : f;
    t = 0 > t ? list_count(list) + t : t;

    if(f == t) { return; }

    t = f < t ? t + 1 : t;

    Node node_f = node_at((Node)list, f);
    if(NULL == node_f) { return; }

    Node node_t = node_at((Node)list, t);
    if(NULL == node_t) { return; }

    node_insert_node(node_t, node_remove(node_f));
}

Index list_indexof(List list, Value value) {
    return index_of((Node)list, value);
}

/**
 * @brief 
 * 
 * @param list 
 * @param index -count <= index <= count-1
 * @return Value 
 */
Value list_valueat(List list, Index index) {
    return value_at(list, 0 > index ? list_count(list) + index : index);
}

typedef struct {
    ValueIterator iterator;
    void*         voidargs;
} list_foreach_node_iter_args;

static bool list_foreach_node_iter(Index index, Node node, void* voidargs) {
    list_foreach_node_iter_args* args = (list_foreach_node_iter_args*)voidargs;
    return NULL != node->next && args->iterator(index, node->next->value, args->voidargs);
}

void list_foreach(List list, ValueIterator iterator, void* voidargs) {
    list_foreach_node_iter_args args = {iterator, voidargs};
    node_iteration((Node)list, list_foreach_node_iter, &args);
}
