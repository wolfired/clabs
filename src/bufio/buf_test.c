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

static void test_buf_write_read(void** state) {
    Buffer buf = (Buffer) * (Buffer*)*state;

    buf_write_uint8(buf, 0x12);
    assert_int_equal(1, buf_len(buf));

    buf_write_uint16_be(buf, 0x1234);
    assert_int_equal(3, buf_len(buf));
    buf_write_uint16_le(buf, 0x1234);
    assert_int_equal(5, buf_len(buf));

    buf_write_uint32_be(buf, 0x12345678);
    assert_int_equal(9, buf_len(buf));
    buf_write_uint32_le(buf, 0x12345678);
    assert_int_equal(13, buf_len(buf));

    buf_write_uint64_be(buf, 0x1234567890987654);
    assert_int_equal(21, buf_len(buf));
    buf_write_uint64_le(buf, 0x1234567890987654);
    assert_int_equal(29, buf_len(buf));

    assert_int_equal(0x12, buf_read_uint8(buf));
    assert_int_equal(0x1234, buf_read_uint16_be(buf));
    assert_int_equal(0x1234, buf_read_uint16_le(buf));
    assert_int_equal(0x12345678, buf_read_uint32_be(buf));
    assert_int_equal(0x12345678, buf_read_uint32_le(buf));
    assert_int_equal(0x1234567890987654, buf_read_uint64_be(buf));
    assert_int_equal(0x1234567890987654, buf_read_uint64_le(buf));
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test_setup_teardown(test_buf_create_len_cap_delete, setup, teardown),
        cmocka_unit_test_setup_teardown(test_buf_write_read, setup, teardown),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
