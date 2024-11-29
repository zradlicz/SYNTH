#ifndef DOUBLE_BUFFER_H
#define DOUBLE_BUFFER_H

#include <stdint.h>
#include <stddef.h>

#define BUFFER_SIZE 4410 // Example buffer size: 1/10 second at 44.1 kHz

// Opaque type
typedef struct DoubleBuffer_S * DoubleBuffer_T;

// Initialize the double buffer
DoubleBuffer_T DoubleBuffer_New(void);

// Get active or inactive buffer pointers
int16_t* DoubleBuffer_GetActive(DoubleBuffer_T db);
int16_t* DoubleBuffer_GetInactive(DoubleBuffer_T db);

// Swap the active and inactive buffers
void DoubleBuffer_Swap(DoubleBuffer_T db);

// Clear both buffers
void DoubleBuffer_Clear(DoubleBuffer_T db);

// get size of buffer
size_t DoubleBuffer_GetSize(DoubleBuffer_T db);

#endif // DOUBLE_BUFFER_H
