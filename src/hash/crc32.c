#include <stdint.h>
#include <stddef.h>

#include "hash/crc32.h"

inline void crc32_update_byte(uint32_t* p_crc, const uint8_t byte) {
    static const unsigned table[] = {0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c, 0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c};
    *p_crc ^= byte;
    *p_crc = ((*p_crc) >> 4) ^ table[(*p_crc) & 15];
    *p_crc = ((*p_crc) >> 4) ^ table[(*p_crc) & 15];
}

void crc32_update_bytes(uint32_t* p_crc, const uint8_t* bytes, size_t bytes_count) {
    for (size_t i = 0; i < bytes_count; ++i) {
        crc32_update_byte(p_crc, bytes[i]);
    }
}

uint32_t crc32(const uint8_t* bytes, size_t bytes_count) {
    uint32_t crc = ~0;
    crc32_update_bytes(&crc, bytes, bytes_count);
    return ~crc;
}
