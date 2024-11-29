#ifndef SYNTH_H
#define SYNTH_H

#include <stdint.h>
#include <stddef.h>
#include "buffer.h"
#include "osc.h"

// Synthesizer opaque type
typedef struct Synth_S* Synth_T;

// Initialize the synthesizer
void Synth_Init(Synth_T synth, DoubleBuffer_T* buffer, Oscillator_T* oscillators, size_t num_oscillators);

// Start the synthesizer threads
void Synth_Start(Synth_T synth);

// Stop the synthesizer threads
void Synth_Stop(Synth_T synth);

#endif // SYNTH_H
