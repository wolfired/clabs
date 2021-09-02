#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gc/mark_sweep.h"

#define BLOCK_HEAD_SIZE (sizeof(size_t) + sizeof(size_t))
#define POINTER_SIZE (sizeof(uintptr_t))

typedef struct _Block {
    size_t flag;
    size_t body_size;
    // struct _Block* next_ptr;
} Block;

static uint8_t* heap_head_ptr = NULL;
static uint8_t* heap_tail_ptr = NULL;

static Block* idle_list_head = NULL;

static Block* block_linear_next_ptr_get(Block* block_ptr) { return (Block*)((uint8_t*)block_ptr + BLOCK_HEAD_SIZE + block_ptr->body_size); }

static Block** block_linked_next_ptr_addr_get(Block* block_ptr) {
    if (1 == block_ptr->flag) {
        return NULL;
    }
    return (Block**)((uint8_t*)block_ptr + BLOCK_HEAD_SIZE);
}

static Block* block_linked_next_ptr_get(Block* block_ptr) {
    Block** ptr_addr = block_linked_next_ptr_addr_get(block_ptr);
    if (NULL == ptr_addr) {
        return NULL;
    }
    return *ptr_addr;
}

static void block_linked_next_ptr_set(Block* block_ptr, Block* next_block_ptr) {
    Block** ptr_addr = block_linked_next_ptr_addr_get(block_ptr);
    if (NULL == ptr_addr) {
        return;
    }
    *ptr_addr = next_block_ptr;
}

static void* block_body_ptr_get(Block* block_ptr, size_t offset) { return (void*)((uint8_t*)block_ptr + BLOCK_HEAD_SIZE + offset); }

static Block* foreach_block_linear(uint8_t* heap_head, uint8_t* heap_tail, bool (*handler)(Block*)) {
    while (heap_head < heap_tail) {
        Block* real = (Block*)heap_head;

        if (handler(real)) {
            return real;
        }

        heap_head += BLOCK_HEAD_SIZE + real->body_size;
    }
    return NULL;
}

static Block* foreach_block_linked(Block* list_head, bool (*handler)(Block*)) {
    while (NULL != list_head) {
        Block* real = list_head;

        if (handler(real)) {
            return real;
        }

        list_head = block_linked_next_ptr_get(list_head);
    }
    return NULL;
}

void ms_init(uint8_t* heap_ptr, size_t heap_size) {
    if (NULL != heap_head_ptr) {
        return;
    }
    heap_head_ptr = heap_ptr;
    heap_tail_ptr = heap_head_ptr + heap_size;

    idle_list_head = (Block*)heap_head_ptr;
    idle_list_head->flag = 0;
    idle_list_head->body_size = heap_size - BLOCK_HEAD_SIZE;
    block_linked_next_ptr_set(idle_list_head, NULL);
}

void* ms_new(size_t need_size) {
    need_size = POINTER_SIZE > need_size ? POINTER_SIZE : need_size;

    Block** prev = &idle_list_head;
    Block* next_block_ptr = *prev;

    while (NULL != next_block_ptr) {
        if (need_size <= next_block_ptr->body_size) {
            break;
        }

        prev = block_linked_next_ptr_addr_get(next_block_ptr);
        next_block_ptr = block_linked_next_ptr_get(next_block_ptr);
    }

    if (NULL == next_block_ptr) {
        return NULL;
    }

    if (need_size == next_block_ptr->body_size || need_size + BLOCK_HEAD_SIZE + POINTER_SIZE > next_block_ptr->body_size) {
        *prev = block_linked_next_ptr_get(next_block_ptr);
        next_block_ptr->flag = 1;
    } else {
        *prev = (Block*)block_body_ptr_get(next_block_ptr, need_size);
        block_linked_next_ptr_set(*prev, block_linked_next_ptr_get(next_block_ptr));
        (*prev)->body_size = next_block_ptr->body_size - need_size - BLOCK_HEAD_SIZE;
        (*prev)->flag = 0;

        next_block_ptr->flag = 1;
        next_block_ptr->body_size = need_size;
    }

    return block_body_ptr_get(next_block_ptr, 0);
}

void ms_mock() {
    int i = 0;

    uint8_t* heap_head = (uint8_t*)heap_head_ptr;
    uint8_t* heap_tail = (uint8_t*)heap_tail_ptr;
    while (heap_head < heap_tail) {
        Block* real = (Block*)heap_head;

        if (1 == real->flag) {
            real->flag = 6 > (rand() % 10) ? 0 : 1;
        }

        heap_head += BLOCK_HEAD_SIZE + real->body_size;
    }
}

void ms_sweep() {
    Block** prev = &idle_list_head;

    uint8_t* heap_head = (uint8_t*)heap_head_ptr;
    uint8_t* heap_tail = (uint8_t*)heap_tail_ptr;
    while (heap_head < heap_tail) {
        Block* real = (Block*)heap_head;

        if (0 == real->flag) {
            Block* linear_next = block_linear_next_ptr_get(real);
            if (NULL != linear_next && 0 == linear_next->flag) {
                real->body_size += BLOCK_HEAD_SIZE + linear_next->body_size;
            } else {
                *prev = real;
                prev = block_linked_next_ptr_addr_get(real);
                heap_head += BLOCK_HEAD_SIZE + real->body_size;
            }
        } else {
            real->flag = 0;
            heap_head += BLOCK_HEAD_SIZE + real->body_size;
        }
    }
}

void ms_snapshoot(uint8_t* png) {
    size_t i = 0;

    uint8_t* heap_head = (uint8_t*)heap_head_ptr;
    uint8_t* heap_tail = (uint8_t*)heap_tail_ptr;
    while (heap_head < heap_tail) {
        Block* real = (Block*)heap_head;

        uint8_t* begin = (uint8_t*)real;
        uint8_t* end = (uint8_t*)block_linear_next_ptr_get(real);

        while (begin < end) {
            png[i + 0] = 1 == real->flag ? 255 : 0;
            png[i + 1] = 0 == real->flag ? 255 : 0;
            png[i + 2] = 0;
            png[i + 3] = 255;

            begin += 1;
            i += 4;
        }

        heap_head += BLOCK_HEAD_SIZE + real->body_size;
    }
}
