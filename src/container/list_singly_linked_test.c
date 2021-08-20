#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <cmocka.h>

#define UNIT_TESTINT

#ifdef UNIT_TESTINT
#define malloc test_malloc
#define realloc test_realloc
#define calloc test_calloc
#define free test_free
#endif

#include "list_singly_linked.h"

static int setup(void** state) {
    List* plist = (List*)malloc(sizeof(List));
    *plist = NULL;
    list_create(plist);
    assert_non_null(*plist);
    *state = plist;
    return 0;
}

static int teardown(void** state) {
    List* plist = (List*)*state;
    list_destory(plist);
    assert_null(*plist);
    free(plist);
    return 0;
}

static void test_list_create_count_destory(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));
}

static void test_list_insert_count_count_set(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));

    list_count_set(list, 0);
    assert_int_equal(0, list_count(list));
    list_insert(list, list_count(list) + 1, NULL);
    list_insert(list, -list_count(list) - 1 - 1, NULL);
    list_insert(list, 1, NULL);
    list_insert(list, -2, NULL);
    list_insert(list, 0, NULL);
    list_insert(list, 1, NULL);
    list_insert(list, -1, NULL);
    list_insert(list, list_count(list), NULL);
    list_insert(list, -list_count(list) - 1, NULL);
    assert_int_equal(5, list_count(list));

    list_count_set(list, 0);
    assert_int_equal(0, list_count(list));
    list_insert(list, -1, NULL);
    list_insert(list, 1, NULL);
    assert_int_equal(2, list_count(list));
}

static void test_list_insert_valueat(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));

    char* str = "0123456789";

    list_insert(list, 0, str + 9);
    list_insert(list, -1, str + 7);
    list_insert(list, 0, str + 3);
    list_insert(list, 0, str + 0);
    assert_int_equal(4, list_count(list));
    list_insert(list, 4 + 1, str + 1);
    list_insert(list, -4 - 1, str + 2);
    assert_int_equal(5, list_count(list));
    list_insert(list, -5 - 1 - 1, str + 8);
    list_insert(list, 1, str + 6);
    list_insert(list, -1, str + 5);
    assert_int_equal(7, list_count(list));
    assert_int_equal((char)'2', *(char*)list_valueat(list, 0));
    assert_int_equal((char)'6', *(char*)list_valueat(list, 1));
    assert_int_equal((char)'0', *(char*)list_valueat(list, 2));
    assert_int_equal((char)'3', *(char*)list_valueat(list, 3));
    assert_int_equal((char)'9', *(char*)list_valueat(list, 4));
    assert_int_equal((char)'7', *(char*)list_valueat(list, 5));
    assert_int_equal((char)'5', *(char*)list_valueat(list, 6));
}

static void test_list_insert_indexof(void** state) {
    List list = (List) * (List*)*state;
    assert_int_equal(0, list_count(list));

    char* str = "0123456789";

    list_insert(list, list_count(list), str + 9);
    list_insert(list, list_count(list), str + 0);
    list_insert(list, -1, str + 2);
    list_insert(list, -1, str + 5);
    list_insert(list, -list_count(list)-1, str + 6);
    list_insert(list, -list_count(list)-1, str + 8);
    list_insert(list, 0, str + 3);
    list_insert(list, 0, str + 7);
    list_insert(list, 5, str + 1);
    list_insert(list, -3, str + 4);
    assert_int_equal(10, list_count(list));
    assert_int_equal(0, list_indexof(list, str + 7));
    assert_int_equal(1, list_indexof(list, str + 3));
    assert_int_equal(2, list_indexof(list, str + 8));
    assert_int_equal(3, list_indexof(list, str + 6));
    assert_int_equal(4, list_indexof(list, str + 9));
    assert_int_equal(5, list_indexof(list, str + 1));
    assert_int_equal(6, list_indexof(list, str + 0));
    assert_int_equal(7, list_indexof(list, str + 4));
    assert_int_equal(8, list_indexof(list, str + 2));
    assert_int_equal(9, list_indexof(list, str + 5));
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test_setup_teardown(test_list_create_count_destory, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_insert_count_count_set, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_insert_valueat, setup, teardown),
        cmocka_unit_test_setup_teardown(test_list_insert_indexof, setup, teardown),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
