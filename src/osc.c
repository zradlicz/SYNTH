#include "osc.h"
#include <math.h>
#include <string.h>

#define PI 3.14159265358979323846

struct Oscillator_S {
    double frequency;
    int amplitude;
    double phase;
    double sample_rate;
    WaveformType waveform_type;
};

void oscillator_init(Oscillator* osc, double sample_rate, WaveformType waveform_type) {
    osc->frequency = 440.0;  // Default frequency (A4)
    osc->amplitude = 32767; // Default amplitude for 16-bit audio
    osc->phase = 0.0;
    osc->sample_rate = sample_rate;
    osc->waveform_type = waveform_type;
}

void oscillator_set_frequency(Oscillator* osc, double frequency) {
    osc->frequency = frequency;
}

void oscillator_set_amplitude(Oscillator* osc, int amplitude) {
    osc->amplitude = amplitude;
}

void oscillator_set_waveform(Oscillator* osc, WaveformType waveform_type) {
    osc->waveform_type = waveform_type;
}

void oscillator_generate(Oscillator* osc, int16_t* buffer, size_t num_samples) {
    double increment = 2.0 * PI * osc->frequency / osc->sample_rate;

    for (size_t i = 0; i < num_samples; ++i) {
        switch (osc->waveform_type) {
            case WAVEFORM_SINE:
                buffer[i] = (int16_t)(osc->amplitude * sin(osc->phase));
                break;
            case WAVEFORM_SQUARE:
                buffer[i] = (osc->phase < PI) ? osc->amplitude : -osc->amplitude;
                break;
            default:
                buffer[i] = 0; // Default to silence if waveform is unknown
                break;
        }
        osc->phase += increment;
        if (osc->phase >= 2.0 * PI) {
            osc->phase -= 2.0 * PI;
        }
    }
}
