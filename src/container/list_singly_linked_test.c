#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#define UNIT_TESTINT

#ifdef UNIT_TESTINT
#define malloc test_malloc
#define realloc test_realloc
#define calloc test_calloc
#define free test_free
#endif

#include "list_singly_linked.h"

typedef struct {
    char stop_at;
    char record[1024];
} print_each_args;

bool print_each(Index index, Value value, void* voidargs) {
    // printf("%d -> %c\n", index, (char)*(char*)value);
    print_each_args* args = (print_each_args*)voidargs;
    args->record[index]   = (char)*(char*)value;
    return 0 == args->stop_at || args->stop_at != (char)*(char*)value;
}

char* make_list(char* str, List list) {
    list_insert(list, list_count(list), str + 2);
    list_insert(list, -list_count(list) - 1, str + 1);
    list_insert(list, list_count(list), str + 3);
    list_insert(list, -list_count(list) - 1, str + 0);
    assert_int_equal(4, list_count(list));
    return str;
}

static int setup(void** state) {
    List* p_list = (List*)malloc(sizeof(List));

    *p_list = NULL;

    list_create(p_list);
    assert_non_null(*p_list);

    *state = p_list;

    return 0;
}

static int teardown(void** state) {
    List* p_list = (List*)*state;
    list_delete(p_list);
    assert_null(*p_list);
    free(p_list);
    return 0;
}

static void test_list_create_count_delete(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));
}

static void test_list_insert_count_count_set(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));

    list_insert(list, list_count(list) + 1, NULL);
    list_insert(list, -list_count(list) - 1 - 1, NULL);
    assert_int_equal(0, list_count(list));

    list_insert(list, list_count(list), NULL);
    list_insert(list, -list_count(list) - 1, NULL);
    assert_int_equal(2, list_count(list));

    list_insert(list, list_count(list) + 1, NULL);
    list_insert(list, -list_count(list) - 1 - 1, NULL);
    assert_int_equal(2, list_count(list));

    list_count_set(list, 1);
    assert_int_equal(1, list_count(list));
}

static void test_list_valueat(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));

    assert_null(list_valueat(list, list_count(list) - 1));
    assert_null(list_valueat(list, -list_count(list)));

    char* str = make_list("0123", list);

    assert_null(list_valueat(list, list_count(list)));
    assert_null(list_valueat(list, -list_count(list) - 1));

    assert_int_equal((char)'3', *(char*)list_valueat(list, list_count(list) - 1));
    assert_int_equal((char)'0', *(char*)list_valueat(list, -list_count(list)));
}

static void test_list_indexof(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));
    assert_int_equal(-1, list_indexof(list, (Value)1));

    char* str = make_list("0123", list);

    assert_int_equal(0, list_indexof(list, str + 0));
    assert_int_equal(1, list_indexof(list, str + 1));
    assert_int_equal(2, list_indexof(list, str + 2));
    assert_int_equal(3, list_indexof(list, str + 3));
}

static void test_list_remove(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));

    Value value = NULL;

    assert_int_equal(0, list_remove(list, list_count(list) - 1, &value));
    assert_null(value);
    assert_int_equal(0, list_remove(list, -list_count(list), &value));
    assert_null(value);

    char* str = make_list("0123", list);

    assert_int_equal(4, list_remove(list, list_count(list), &value));
    assert_null(value);
    assert_int_equal(4, list_remove(list, -list_count(list) - 1, &value));
    assert_null(value);

    assert_int_equal(3, list_remove(list, list_count(list) - 1, &value));
    assert_non_null(value);
    assert_int_equal((char)'3', *(char*)value);

    assert_int_equal(2, list_remove(list, -list_count(list), &value));
    assert_non_null(value);
    assert_int_equal((char)'0', *(char*)value);

    assert_int_equal(1, list_remove(list, list_count(list) - 1, &value));
    assert_non_null(value);
    assert_int_equal((char)'2', *(char*)value);

    assert_int_equal(0, list_remove(list, -list_count(list), &value));
    assert_non_null(value);
    assert_int_equal((char)'1', *(char*)value);

    assert_int_equal(0, list_count(list));
}

static void test_list_update(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));

    assert_ptr_equal(NULL, list_update(list, list_count(list) - 1, NULL));
    assert_ptr_equal(NULL, list_update(list, -list_count(list), NULL));

    char* str = make_list("01234567", list);

    assert_ptr_equal(NULL, list_update(list, list_count(list), NULL));
    assert_ptr_equal(NULL, list_update(list, -list_count(list) - 1, NULL));

    assert_int_equal((char)'3', *(char*)list_update(list, list_count(list) - 1, str + 7));
    assert_int_equal((char)'0', *(char*)list_update(list, -list_count(list), str + 4));

    assert_int_equal((char)'7', *(char*)list_valueat(list, list_count(list) - 1));
    assert_int_equal((char)'4', *(char*)list_valueat(list, -list_count(list)));
    assert_int_equal(4, list_count(list));
}

static void test_list_swap(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));

    list_swap(list, list_count(list) - 1, -list_count(list));
    list_swap(list, -list_count(list), list_count(list) - 1);
    assert_int_equal(0, list_count(list));

    char* str = make_list("0123", list);

    list_swap(list, list_count(list), -list_count(list) - 1);
    list_swap(list, -list_count(list) - 1, list_count(list));

    list_swap(list, 0, list_count(list));

    list_swap(list, list_count(list) - 1, -list_count(list));
    assert_int_equal((char)'0', *(char*)list_valueat(list, list_count(list) - 1));
    assert_int_equal((char)'3', *(char*)list_valueat(list, -list_count(list)));
    list_swap(list, -list_count(list), list_count(list) - 1);
    assert_int_equal((char)'3', *(char*)list_valueat(list, list_count(list) - 1));
    assert_int_equal((char)'0', *(char*)list_valueat(list, -list_count(list)));
    assert_int_equal(4, list_count(list));
}

static void test_list_move(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));

    list_move(list, list_count(list) - 1, -list_count(list));
    list_move(list, -list_count(list), list_count(list) - 1);
    assert_int_equal(0, list_count(list));

    char* str = make_list("0123", list);

    list_move(list, list_count(list), -list_count(list) - 1);
    list_move(list, -list_count(list) - 1, list_count(list));

    list_move(list, list_count(list) - 1, -1);
    list_move(list, 0, -list_count(list));

    list_move(list, list_count(list) - 1, -list_count(list));
    assert_int_equal((char)'2', *(char*)list_valueat(list, list_count(list) - 1));
    assert_int_equal((char)'3', *(char*)list_valueat(list, -list_count(list)));

    list_move(list, -list_count(list), list_count(list) - 1);
    assert_int_equal((char)'3', *(char*)list_valueat(list, list_count(list) - 1));
    assert_int_equal((char)'0', *(char*)list_valueat(list, -list_count(list)));
    assert_int_equal(4, list_count(list));
}

static void test_list_insert_foreach(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));

    print_each_args args;

    args.stop_at = 0;
    memset(args.record, 0, 1024);
    list_foreach(list, print_each, &args);
    assert_int_equal(0, strcmp("", args.record));

    char* str = make_list("0123", list);

    args.stop_at = 0;
    memset(args.record, 0, 1024);
    list_foreach(list, print_each, &args);
    assert_int_equal(0, strcmp(str, args.record));

    args.stop_at = '2';
    memset(args.record, 0, 1024);
    list_foreach(list, print_each, &args);
    assert_int_equal(0, strcmp("012", args.record));
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test_setup_teardown(test_list_create_count_delete, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_insert_count_count_set, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_insert_foreach, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_valueat, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_indexof, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_remove, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_update, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_swap, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_move, setup, teardown),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
