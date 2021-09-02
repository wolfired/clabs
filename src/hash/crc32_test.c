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

#include "hash/crc32.h"

#define UNIT_TESTINT

#ifdef UNIT_TESTINT
#define malloc test_malloc
#define realloc test_realloc
#define calloc test_calloc
#define free test_free
#endif

static void test_crc32(void** state) {
    char* str;
    str = "";
    assert_int_equal(0x00000000, crc32(str, strlen(str)));

	str = "a";
    assert_int_equal(0xe8b7be43, crc32(str, strlen(str)));

	str = "ab";
    assert_int_equal(0x9e83486d, crc32(str, strlen(str)));

	str = "abc";
    assert_int_equal(0x352441c2, crc32(str, strlen(str)));

	str = "abcd";
    assert_int_equal(0xed82cd11, crc32(str, strlen(str)));

	str = "abcde";
    assert_int_equal(0x8587d865, crc32(str, strlen(str)));

	str = "abcdef";
    assert_int_equal(0x4b8e39ef, crc32(str, strlen(str)));

	str = "abcdefg";
    assert_int_equal(0x312a6aa6, crc32(str, strlen(str)));

	str = "abcdefgh";
    assert_int_equal(0xaeef2a50, crc32(str, strlen(str)));

	str = "abcdefghi";
    assert_int_equal(0x8da988af, crc32(str, strlen(str)));

	str = "abcdefghij";
    assert_int_equal(0x3981703a, crc32(str, strlen(str)));

	str = "Discard medicine more than two years old.";
    assert_int_equal(0x6b9cdfe7, crc32(str, strlen(str)));

	str = "He who has a shady past knows that nice guys finish last.";
    assert_int_equal(0xc90ef73f, crc32(str, strlen(str)));

	str = "I wouldn't marry him with a ten foot pole.";
    assert_int_equal(0xb902341f, crc32(str, strlen(str)));

	str = "Free! Free!/A trip/to Mars/for 900/empty jars/Burma Shave";
    assert_int_equal(0x042080e8, crc32(str, strlen(str)));

	str = "The days of the digital watch are numbered.  -Tom Stoppard";
    assert_int_equal(0x154c6d11, crc32(str, strlen(str)));

	str = "Nepal premier won't resign.";
    assert_int_equal(0x4c418325, crc32(str, strlen(str)));

	str = "For every action there is an equal and opposite government program.";
    assert_int_equal(0x33955150, crc32(str, strlen(str)));

	str = "His money is twice tainted: 'taint yours and 'taint mine.";
    assert_int_equal(0x26216a4b, crc32(str, strlen(str)));

	str = "There is no reason for any individual to have a computer in their home. -Ken Olsen, 1977";
    assert_int_equal(0x1abbe45e, crc32(str, strlen(str)));

	str = "It's a tiny change to the code and not completely disgusting. - Bob Manchek";
    assert_int_equal(0xc89a94f7, crc32(str, strlen(str)));

	str = "size:  a.out:  bad magic";
    assert_int_equal(0xab3abe14, crc32(str, strlen(str)));

	str = "The major problem is with sendmail.  -Mark Horton";
    assert_int_equal(0xbab102b6, crc32(str, strlen(str)));

	str = "Give me a rock, paper and scissors and I will move the world.  CCFestoon";
    assert_int_equal(0x999149d7, crc32(str, strlen(str)));

	str = "If the enemy is within range, then so are you.";
    assert_int_equal(0x6d52a33c, crc32(str, strlen(str)));

	str = "It's well we cannot hear the screams/That we create in others' dreams.";
    assert_int_equal(0x90631e8d, crc32(str, strlen(str)));

	str = "You remind me of a TV show, but that's all right: I watch it anyway.";
    assert_int_equal(0x78309130, crc32(str, strlen(str)));

	str = "C is as portable as Stonehedge!!";
    assert_int_equal(0x7d0a377f, crc32(str, strlen(str)));

	str = "Even if I could be Shakespeare, I think I should still choose to be Faraday. - A. Huxley";
    assert_int_equal(0x8c79fd79, crc32(str, strlen(str)));

	str = "The fugacity of a constituent in a mixture of gases at a given temperature is proportional to its mole fraction.  Lewis-Randall Rule";
    assert_int_equal(0xa20b7167, crc32(str, strlen(str)));

	str = "How can you write a big system without C++?  -Paul Glick";
    assert_int_equal(0x8e0bb443, crc32(str, strlen(str)));

}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    const struct CMUnitTest test_group[] = {
        cmocka_unit_test(test_crc32),
    };

    return cmocka_run_group_tests(test_group, NULL, NULL);
}
