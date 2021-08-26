#include <locale.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "buf.h"

#define UNIT_TESTINT

#ifdef UNIT_TESTINT
#define malloc test_malloc
#define realloc test_realloc
#define calloc test_calloc
#define free test_free
#endif

static int setup(void** state) {
    Buffer* p_buf = (Buffer*)malloc(sizeof(Buffer));

    *p_buf = NULL;

    buf_create(p_buf, 128);
    assert_non_null(*p_buf);

    *state = p_buf;

    return 0;
}

static int teardown(void** state) {
    Buffer* p_buf = (Buffer*)*state;
    buf_delete(p_buf);
    assert_null(*p_buf);
    free(p_buf);
    return 0;
}

static void test_buf_create_len_cap_delete(void** state) {
    Buffer buf = (Buffer) * (Buffer*)*state;

    assert_int_equal(0, buf_len(buf));
    assert_int_equal(128, buf_cap(buf));
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test_setup_teardown(test_buf_create_len_cap_delete, setup, teardown),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
