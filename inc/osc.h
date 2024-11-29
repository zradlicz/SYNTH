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
void oscillator_init(Oscillator_T* osc, double sample_rate, WaveformType waveform_type);

// Set properties
void oscillator_set_frequency(Oscillator_T* osc, double frequency);
void oscillator_set_amplitude(Oscillator_T* osc, int amplitude);
void oscillator_set_waveform(Oscillator_T* osc, WaveformType waveform_type);

// Generate waveform samples
void oscillator_generate(Oscillator_T* osc, int16_t* buffer, size_t num_samples);

#endif // OSCILLATOR_H
