#ifndef DOUBLE_BUFFER_H
#define DOUBLE_BUFFER_H

#include <stdint.h>
#include <stddef.h>

#define BUFFER_SIZE 4410 // Example buffer size: 1/10 second at 44.1 kHz

// Opaque type
typedef struct DoubleBuffer DoubleBuffer;

// Initialize the double buffer
void double_buffer_init(DoubleBuffer* db);

// Get active or inactive buffer pointers
int16_t* double_buffer_get_active(DoubleBuffer* db);
int16_t* double_buffer_get_inactive(DoubleBuffer* db);

// Swap the active and inactive buffers
void double_buffer_swap(DoubleBuffer* db);

// Clear both buffers
void double_buffer_clear(DoubleBuffer* db);

#endif // DOUBLE_BUFFER_H
