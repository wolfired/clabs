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

#include "adler32.h"

#define UNIT_TESTINT

#ifdef UNIT_TESTINT
#define malloc test_malloc
#define realloc test_realloc
#define calloc test_calloc
#define free test_free
#endif

static void test_adler32(void** state) {
    char* str;

    str = "";
    assert_int_equal(0x00000001, adler32(str, strlen(str)));

    str = "a";
    assert_int_equal(0x00620062, adler32(str, strlen(str)));

    str = "ab";
    assert_int_equal(0x012600c4, adler32(str, strlen(str)));

    str = "abc";
    assert_int_equal(0x024d0127, adler32(str, strlen(str)));

    str = "abcd";
    assert_int_equal(0x03d8018b, adler32(str, strlen(str)));

    str = "abcde";
    assert_int_equal(0x05c801f0, adler32(str, strlen(str)));

    str = "abcdef";
    assert_int_equal(0x081e0256, adler32(str, strlen(str)));

    str = "abcdefg";
    assert_int_equal(0x0adb02bd, adler32(str, strlen(str)));

    str = "abcdefgh";
    assert_int_equal(0x0e000325, adler32(str, strlen(str)));

    str = "abcdefghi";
    assert_int_equal(0x118e038e, adler32(str, strlen(str)));

    str = "abcdefghij";
    assert_int_equal(0x158603f8, adler32(str, strlen(str)));

    str = "Discard medicine more than two years old.";
    assert_int_equal(0x3f090f02, adler32(str, strlen(str)));

    str = "He who has a shady past knows that nice guys finish last.";
    assert_int_equal(0x46d81477, adler32(str, strlen(str)));

    str = "I wouldn't marry him with a ten foot pole.";
    assert_int_equal(0x40ee0ee1, adler32(str, strlen(str)));

    str = "Free! Free!/A trip/to Mars/for 900/empty jars/Burma Shave";
    assert_int_equal(0x16661315, adler32(str, strlen(str)));

    str = "The days of the digital watch are numbered.  -Tom Stoppard";
    assert_int_equal(0x5b2e1480, adler32(str, strlen(str)));

    str = "Nepal premier won't resign.";
    assert_int_equal(0x8c3c09ea, adler32(str, strlen(str)));

    str = "For every action there is an equal and opposite government program.";
    assert_int_equal(0x45ac18fd, adler32(str, strlen(str)));

    str = "His money is twice tainted: 'taint yours and 'taint mine.";
    assert_int_equal(0x53c61462, adler32(str, strlen(str)));

    str = "There is no reason for any individual to have a computer in their home. -Ken Olsen, 1977";
    assert_int_equal(0x7e511e63, adler32(str, strlen(str)));

    str = "It's a tiny change to the code and not completely disgusting. - Bob Manchek";
    assert_int_equal(0xe4801a6a, adler32(str, strlen(str)));

    str = "size:  a.out:  bad magic";
    assert_int_equal(0x61b507df, adler32(str, strlen(str)));

    str = "The major problem is with sendmail.  -Mark Horton";
    assert_int_equal(0xb8631171, adler32(str, strlen(str)));

    str = "Give me a rock, paper and scissors and I will move the world.  CCFestoon";
    assert_int_equal(0x8b5e1904, adler32(str, strlen(str)));

    str = "If the enemy is within range, then so are you.";
    assert_int_equal(0x7cc6102b, adler32(str, strlen(str)));

    str = "It's well we cannot hear the screams/That we create in others' dreams.";
    assert_int_equal(0x700318e7, adler32(str, strlen(str)));

    str = "You remind me of a TV show, but that's all right: I watch it anyway.";
    assert_int_equal(0x1e601747, adler32(str, strlen(str)));

    str = "C is as portable as Stonehedge!!";
    assert_int_equal(0xb55b0b09, adler32(str, strlen(str)));

    str = "Even if I could be Shakespeare, I think I should still choose to be Faraday. - A. Huxley";
    assert_int_equal(0x39111dd0, adler32(str, strlen(str)));

    str = "The fugacity of a constituent in a mixture of gases at a given temperature is proportional to its mole fraction.  Lewis-Randall Rule";
    assert_int_equal(0x91dd304f, adler32(str, strlen(str)));

    str = "How can you write a big system without C++?  -Paul Glick";
    assert_int_equal(0x2e5d1316, adler32(str, strlen(str)));

    str = "'Invariant assertions' is the most elegant programming technique!  -Tom Szymanski";
    assert_int_equal(0xd0201df6, adler32(str, strlen(str)));
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test(test_adler32),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
