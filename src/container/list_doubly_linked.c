#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "list_doubly_linked.h"

typedef struct _Node {
    Value         value;
    struct _Node* prev;
    struct _Node* next;
} Node_, *Node;

typedef struct _Meta {
    Count count;
} Meta_, *Meta;

static Node node_create(Value value, Node prev, Node next) {
    Node node = (Node)malloc(sizeof(Node_));

    node->value = value;
    node->prev = prev;
    node->next  = next;

    return node;
}

static void node_insert_node(Node node, Node newnode) {
    newnode->next = node->next;
    node->next    = newnode;
    newnode->prev = node;
    newnode->next->prev = newnode;
}
