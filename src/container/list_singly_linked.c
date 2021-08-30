#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "list_singly_linked.h"

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

static Node node_at(List thiz, Index index) {
    node_at_node_iter_args args = {index, NULL};
    node_iteration((Node)thiz, node_at_node_iter, &args);
    return args.node_need;
}

static Value value_at(List thiz, Index index) {
    Node node = node_at(thiz, index);
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

static Node node_of(List thiz, Value value) {
    node_of_node_iter_args args = {value, -1, NULL};
    node_iteration((Node)thiz, node_of_node_iter, &args);
    return args.node_need;
}

static Index index_of(List thiz, Value value) {
    node_of_node_iter_args args = {value, -1, NULL};
    node_iteration((Node)thiz, node_of_node_iter, &args);
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

static inline void count_inc(List thiz) {
    ((Meta)((Node)thiz)->value)->count += 1;
}

static inline void count_dec(List thiz) {
    ((Meta)((Node)thiz)->value)->count -= 1;
}

void list_create(List* p_thiz) {
    *p_thiz = (List)root_create();
}

void list_delete(List* p_thiz) {
    while(node_delete((Node)*p_thiz, NULL)) {}
    root_delete((Node)*p_thiz);
    *p_thiz = NULL;
}

Count list_count(List thiz) {
    return ((Meta)((Node)thiz)->value)->count;
}

Count list_count_set(List thiz, Count count) {
    while(node_delete(node_at(thiz, count), NULL)) { count_dec(thiz); }
    return list_count(thiz);
}

/**
 * @brief
 *
 * @param thiz
 * @param index -count-1 <= i <= count
 * @param value
 * @return Count
 */
Count list_insert(List thiz, Index index, Value value) {
    index = 0 > index ? list_count(thiz) + 1 + index : index;
    if(node_insert_value(node_at(thiz, index), value)) { count_inc(thiz); }
    return list_count(thiz);
}

/**
 * @brief 
 * 
 * @param thiz 
 * @param index -count <= i <= count-1
 * @param p_retval 
 * @return Count 
 */
Count list_remove(List thiz, Index index, Value* p_retval) {
    index = 0 > index ? list_count(thiz) + index : index;
    if(node_delete(node_at(thiz, index), p_retval)) { count_dec(thiz); }
    return list_count(thiz);
}

/**
 * @brief 
 * 
 * @param thiz 
 * @param index -count <= i <= count-1
 * @param newval 
 * @return Value 
 */
Value list_update(List thiz, Index index, Value newval) {
    index = 0 > index ? list_count(thiz) + index : index;
    return node_update(node_at(thiz, index), newval);
}

/**
 * @brief 
 * 
 * @param thiz 
 * @param i -count <= i <= count-1
 * @param j -count <= i <= count-1
 */
void list_swap(List thiz, Index i, Index j) {
    i = 0 > i ? list_count(thiz) + i : i;
    j = 0 > j ? list_count(thiz) + j : j;

    if(i == j) { return; }

    Node node_i = node_at(thiz, i);
    if(NULL == node_i || NULL == node_i->next) { return; }

    Node node_j = node_at(thiz, j);
    if(NULL == node_j) { return; }
    if(NULL == node_j->next) { return; }

    node_i->next->value = (Value)((uintptr_t)node_i->next->value ^ (uintptr_t)node_j->next->value);
    node_j->next->value = (Value)((uintptr_t)node_i->next->value ^ (uintptr_t)node_j->next->value);
    node_i->next->value = (Value)((uintptr_t)node_i->next->value ^ (uintptr_t)node_j->next->value);
}

/**
 * @brief 
 * 
 * @param thiz 
 * @param f -count <= f <= count-1
 * @param t -count <= t <= count-1
 */
void list_move(List thiz, Index f, Index t) {
    f = 0 > f ? list_count(thiz) + f : f;
    t = 0 > t ? list_count(thiz) + t : t;

    if(f == t) { return; }

    t = f < t ? t + 1 : t;

    Node node_f = node_at(thiz, f);
    if(NULL == node_f) { return; }

    Node node_t = node_at(thiz, t);
    if(NULL == node_t) { return; }

    node_insert_node(node_t, node_remove(node_f));
}

/**
 * @brief 
 * 
 * @param thiz 
 * @param index -count <= index <= count-1
 * @return Value 
 */
Value list_valueat(List thiz, Index index) {
    return value_at(thiz, 0 > index ? list_count(thiz) + index : index);
}

Index list_indexof(List thiz, Value value) {
    return index_of(thiz, value);
}

typedef struct {
    ValueIterator iterator;
    void*         voidargs;
} list_foreach_node_iter_args;

static bool list_foreach_node_iter(Index index, Node node, void* voidargs) {
    list_foreach_node_iter_args* args = (list_foreach_node_iter_args*)voidargs;
    return NULL != node->next && args->iterator(index, node->next->value, args->voidargs);
}

void list_foreach(List thiz, ValueIterator iterator, void* voidargs) {
    list_foreach_node_iter_args args = {iterator, voidargs};
    node_iteration((Node)thiz, list_foreach_node_iter, &args);
}
