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
#include "zlib.h"

#define UNIT_TESTINT

#ifdef UNIT_TESTINT
#define malloc test_malloc
#define realloc test_realloc
#define calloc test_calloc
#define free test_free
#endif

static void test_zlib_encode(void** state) {
    Buffer zip_buffer;
    zlib_buf_create(&zip_buffer, zlib_cinfo_default, zlib_cm_default, zlib_level_fastest, zlib_dict_no, 0);

    Buffer compressed_data_buffer;
    buf_create(&compressed_data_buffer, 0);



    // zlib_buf_write_compressed_data(zip_buffer, compressed_data_buffer);

    buf_delete(&compressed_data_buffer);

    zlib_buf_delete(&zip_buffer);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test(test_zlib_encode),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
