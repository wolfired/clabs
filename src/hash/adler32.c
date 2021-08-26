#include <stdint.h>
#include <stddef.h>

#include "adler32.h"

inline void adler32_update_byte(uint32_t* p_adler, uint8_t byte) {
    uint32_t lo = *p_adler & 0xffff;
    uint32_t hi = (*p_adler >> 16) & 0xffff;

    lo = (lo + byte) % 65521;
    hi = (hi + lo) % 65521;

    *p_adler = (hi << 16) + lo;
}

void adler32_update_bytes(uint32_t* p_adler, const uint8_t* bytes, size_t bytes_count) {
    for (size_t i = 0; i < bytes_count; ++i) {
        adler32_update_byte(p_adler, bytes[i]);
    }
}

uint32_t adler32(const uint8_t* bytes, size_t bytes_count) {
    uint32_t adler = 1;
    adler32_update_bytes(&adler, bytes, bytes_count);
    return adler;
}
