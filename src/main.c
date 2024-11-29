#include "osc.h"
#include "synth.h"
#include "output.h"
#include <stdio.h>
#include <stdbool.h>

#define SAMPLE_RATE 44100

static Synth_T synth;
static Oscillator_T osc1;
static Oscillator_T osc2;

int main() {
    synth = Synth_New();

    osc1 = Oscillator_New(WAVEFORM_SQUARE);
    osc2 = Oscillator_New(WAVEFORM_SINE);

    Oscillator_SetFrequency(osc1, 440.0);
    Oscillator_SetFrequency(osc2, 880.0);
    
    Oscillator_SetAmplitude(osc1, 10000);
    Oscillator_SetAmplitude(osc2, 5000);

    Synth_AddOscillator(synth, osc1);
    Synth_AddOscillator(synth, osc2);
    
    printf("Starting audio generation\n");
    while(true)
    {
        Synth_Run(synth, OUTPUT_FILE);
    }
    
    return 0;
}
