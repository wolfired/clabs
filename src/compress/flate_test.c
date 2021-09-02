#include <locale.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "buf.h"
#include "flate.h"

#define UNIT_TESTINT

#ifdef UNIT_TESTINT
#define malloc test_malloc
#define realloc test_realloc
#define calloc test_calloc
#define free test_free
#endif

static void test_deflate_block_0(void** state) {
    Buffer compress = NULL;
    buf_create(&compress, 0);

    Buffer compressed = NULL;
    buf_create(&compressed, 0);

    deflate_block(deflate_final_yes, deflate_type_no, compress, compressed);
    assert_int_equal(5, buf_len(compressed));

    uint8_t  bytes[] = {1, 0, 0, 255, 255};
    assert_int_equal(0, memcmp(bytes, buf_take_pointer(compressed, 0), buf_len(compressed)));

    buf_delete(&compress);
    buf_delete(&compressed);
}

static void test_deflate_block_1(void** state) {
    Buffer compress = NULL;
    buf_create(&compress, 0);

    Buffer compressed = NULL;
    buf_create(&compressed, 0);

    deflate_block(deflate_final_yes, deflate_type_no, compress, compressed);
    assert_int_equal(5, buf_len(compressed));

    uint8_t  bytes[] = {1, 0, 0, 255, 255};
    assert_int_equal(0, memcmp(bytes, buf_take_pointer(compressed, 0), buf_len(compressed)));

    buf_delete(&compress);
    buf_delete(&compressed);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test(test_deflate_block_0),
        cmocka_unit_test(test_deflate_block_1),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
