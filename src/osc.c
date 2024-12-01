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

Oscillator_T Oscillator_New(WaveformType waveform_type) {
    static struct Oscillator_S osc;
    Oscillator_T me = &osc;
    me->frequency = 440.0;  // Default frequency (A4)
    me->amplitude = 32767; // Default amplitude for 16-bit audio
    me->phase = 0.0;
    me->sample_rate = 41000.0; // Default sample rate
    me->waveform_type = waveform_type;
    return me;
}

void Oscillator_SetFrequency(Oscillator_T osc, double frequency) {
    osc->frequency = frequency;
}

void Oscillator_SetAmplitude(Oscillator_T osc, int amplitude) {
    osc->amplitude = amplitude;
}

void Oscillator_SetWaveform(Oscillator_T osc, WaveformType waveform_type) {
    osc->waveform_type = waveform_type;
}

void Oscillator_Generate(Oscillator_T osc, int16_t * data, size_t size) {
    double increment = 2.0 * PI * osc->frequency / osc->sample_rate;
    for (size_t i = 0; i < 3; i++) 
    {
        switch (osc->waveform_type) 
        {
            case WAVEFORM_SINE:
                data[i] = (int16_t)(osc->amplitude * sin(osc->phase));
                break;
            case WAVEFORM_SQUARE:
                data[i] = (osc->phase < PI) ? osc->amplitude : -osc->amplitude;
                break;
            default:
                data[i] = 0; // Default to silence if waveform is unknown
                break;
        }
        osc->phase += increment;
        if (osc->phase >= 2.0 * PI) 
        {
            osc->phase -= 2.0 * PI;
        }
    }
}
