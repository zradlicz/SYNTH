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
typedef struct Oscillator Oscillator;

// Initialize the oscillator
void oscillator_init(Oscillator* osc, double sample_rate, WaveformType waveform_type);

// Set properties
void oscillator_set_frequency(Oscillator* osc, double frequency);
void oscillator_set_amplitude(Oscillator* osc, int amplitude);
void oscillator_set_waveform(Oscillator* osc, WaveformType waveform_type);

// Generate waveform samples
void oscillator_generate(Oscillator* osc, int16_t* buffer, size_t num_samples);

#endif // OSCILLATOR_H
