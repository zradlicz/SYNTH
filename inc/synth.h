#ifndef SYNTH_H
#define SYNTH_H

#include <stdint.h>

//opaque type
typedef struct Synth_S * Synth_T;

Synth_T Synth_New(void);
void Synth_AddOscillator(Synth_T synth, Oscillator_T osc);
void Synth_Run(Synth_T synth, OutputType_t output_type);

uint16_t multiply(uint16_t a, uint16_t b);
uint16_t add_numbers(uint16_t a, uint16_t b);

#endif // SYNTH_H
