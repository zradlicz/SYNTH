#include "osc.h"
#include <math.h>
#include <string.h>
#include <buffer.h>

#define PI 3.14159265358979323846

struct Oscillator_S {
    double frequency;
    int amplitude;
    double phase;
    double sample_rate;
    DoubleBuffer_T audio_buffer;
    WaveformType waveform_type;
};

Oscillator_T Oscillator_New(WaveformType waveform_type) {
    Oscillator_T osc;
    osc->frequency = 440.0;  // Default frequency (A4)
    osc->amplitude = 32767; // Default amplitude for 16-bit audio
    osc->phase = 0.0;
    osc->sample_rate = 41000.0; // Default sample rate
    osc->audio_buffer = DoubleBuffer_New();
    osc->waveform_type = waveform_type;
    return osc;
}

void Oscillator_set_frequency(Oscillator_T osc, double frequency) {
    osc->frequency = frequency;
}

void Oscillator_set_amplitude(Oscillator_T osc, int amplitude) {
    osc->amplitude = amplitude;
}

void Oscillator_set_waveform(Oscillator_T osc, WaveformType waveform_type) {
    osc->waveform_type = waveform_type;
}

void Oscillator_generate(Oscillator_T osc) {
    double increment = 2.0 * PI * osc->frequency / osc->sample_rate;
    int16_t* buffer[BUFFER_SIZE] = DoubleBuffer_GetInactive(osc->audio_buffer);
    for (size_t i = 0; i < DoubleBuffer_GetSize(osc->audio_buffer); ++i) 
    {
        switch (osc->waveform_type) 
        {
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
        if (osc->phase >= 2.0 * PI) 
        {
            osc->phase -= 2.0 * PI;
        }
    }
    DoubleBuffer_Swap(osc->audio_buffer);
}
