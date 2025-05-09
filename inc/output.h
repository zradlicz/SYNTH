#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdint.h>
#include <stddef.h>

// Define output types
typedef enum {
    OUTPUT_ALSA,
    OUTPUT_FILE
} OutputType_t;

//output to ALSA
void Output_ALSA(int16_t * buffer, size_t size);

//output to file
void Output_File(int16_t * buffer, size_t size);

#endif // OUTPUT_H