#ifndef CRC32_H
#define CRC32_H

inline void crc32_update_byte(uint32_t* p_crc, const uint8_t byte);
void crc32_update_bytes(uint32_t* p_crc, const uint8_t* bytes, size_t bytes_count);
uint32_t crc32(const uint8_t* bytes, size_t bytes_count);

#endif
