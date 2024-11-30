#ifndef SYNTH_H
#define SYNTH_H

#include "osc.h"     // Include your oscillator implementation
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_OSCILLATORS 16

// Opaque type for Synth
typedef struct Synth_S* Synth_T;

// Functions to manage Synth lifecycle
Synth_T Synth_New(void);
void Synth_AddOscillator(Synth_T synth, Oscillator_T osc);
void Synth_Start(Synth_T synth);
void Synth_Stop(Synth_T synth);

#endif // SYNTH_H
