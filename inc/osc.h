#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <stdint.h>
#include <stddef.h>

// Define waveform types
typedef enum {
    WAVEFORM_SINE,
    WAVEFORM_SQUARE
} WaveformType;

// Opaque type
typedef struct Oscillator_S * Oscillator_T;

// Initialize the oscillator
Oscillator_T Oscillator_New(WaveformType waveform_type);

// Set properties
void Oscillator_SetFrequency(Oscillator_T osc, double frequency);
void Oscillator_SetAmplitude(Oscillator_T osc, int amplitude);
void Oscillator_SetWaveform(Oscillator_T osc, WaveformType waveform_type);

// Generate waveform samples
void Oscillator_Generate(Oscillator_T osc);

#endif // OSCILLATOR_H
