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
#include "image/png.h"

#define UNIT_TESTINT

#ifdef UNIT_TESTINT
#define malloc test_malloc
#define realloc test_realloc
#define calloc test_calloc
#define free test_free
#endif

static void test_png(void** state) {
    // clang-format off
    uint8_t pixel_bytes[] = {
        0xff,0x00,0x00,0xff,
        0x00,0xff,0x00,0xff,
        0x00,0x00,0xff,0xff,
        0xff,0xff,0xff,0xff,
        // 0xff,0x00,0x00,0xff,
        // 0xff,0x00,0x00,0xff,
        // 0xff,0x00,0x00,0xff,
        // 0xff,0x00,0x00,0xff,
    };
    // clang-format on

    Buffer buffer_png = NULL;
    buf_create(&buffer_png, 1024);

    png_encode_pixel_bytes(buffer_png, 2, 2, pixel_bytes);

    uint8_t* p = buf_take_pointer(buffer_png, 0);
    size_t   l = buf_len(buffer_png);
    // for(size_t i = 0; i < l; ++i) { printf("%02x ", p[i]); }

    FILE* file = fopen("./a.png", "wb");

    fwrite(p, buf_len(buffer_png), 1, file);

    fclose(file);

    buf_delete(&buffer_png);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test(test_png),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
