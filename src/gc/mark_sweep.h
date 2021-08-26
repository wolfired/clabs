#ifndef MARK_SWEEP_H
#define MARK_SWEEP_H

void ms_init(uint8_t* heap_ptr, size_t heap_size);
void* ms_new(size_t need_size);
void ms_mock();
void ms_sweep();
void ms_snapshoot(uint8_t* png);

#endif
