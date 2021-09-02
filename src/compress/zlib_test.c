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

#include "bufio/buf.h"
#include "compress/flate.h"
#include "compress/zlib.h"

#define UNIT_TESTINT

#ifdef UNIT_TESTINT
#define malloc test_malloc
#define realloc test_realloc
#define calloc test_calloc
#define free test_free
#endif

static void test_zlib_encode(void** state) {
    Buffer buffer_zlib;
    zlib_buf_create(&buffer_zlib, zlib_cinfo_default, zlib_cm_default, zlib_level_fastest, zlib_dict_no, 0);

    Buffer buffer_uncompress;
    buf_create(&buffer_uncompress, 0);

    Buffer buffer_compressed;
    buf_create(&buffer_compressed, 0);

    // buf_write_bytes(buffer_uncompress, {0}, 1);

    // deflate_write_block(deflate_final_yes, deflate_type_no, NULL, buffer_compressed);

    // zlib_buf_write_compressed_data(buffer_zlib, buffer_compressed);

    buf_delete(&buffer_uncompress);
    buf_delete(&buffer_compressed);
    zlib_buf_delete(&buffer_zlib);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test(test_zlib_encode),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
