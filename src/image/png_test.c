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
#include "png.h"

#define UNIT_TESTINT

#ifdef UNIT_TESTINT
#define malloc test_malloc
#define realloc test_realloc
#define calloc test_calloc
#define free test_free
#endif

static void test_png(void** state) {
    // uint8_t* png = malloc(2 * 2 * 4);
    // for(size_t i = 0; i < 4; i++) {
    //     png[i * 4 + 0] = 0xff;
    //     png[i * 4 + 1] = 0x0;
    //     png[i * 4 + 2] = 0x0;
    //     png[i * 4 + 3] = 0xff;
    // }

    // Buffer buf = NULL;
    // buf_create(&buf, 1024);

    // png_encode(png, 2, 2, buf);

    // uint8_t* p = buf_take_pointer(buf, 0);
    // size_t   l = buf_len(buf);
    // for(size_t i = 0; i < l; ++i) { printf("%02x ", p[i]); }

    // FILE* file = fopen("./a.png", "wb");

    // fwrite(p, 1, buf_len(buf), file);

    // fclose(file);
    // free(png);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test(test_png),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
