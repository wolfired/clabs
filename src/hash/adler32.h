#ifndef ADLER32_H
#define ADLER32_H

void adler32_update_byte(uint32_t* p_adler, uint8_t byte);
void adler32_update_bytes(uint32_t* p_adler, const uint8_t* bytes, size_t bytes_count);
uint32_t adler32(const uint8_t* bytes, size_t bytes_count);

#endif
