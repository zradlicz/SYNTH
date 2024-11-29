#include <stdio.h>
#include <stdint.h>
#include "math.h"
#include "synth.h"
#include "osc.h"
#include "output.h"


static struct Synth_S 
{
    Oscillator_T oscillators[16];
    //Effects_T effects[16];
};

Synth_T Synth_New(void)
{
    return Synth_T synth;
}

void Synth_AddOscillator(Synth_T synth, Oscillator_T osc) 
{
    for (size_t i = 0; i < 16; ++i) 
    {
        if (synth->oscillators[i] == NULL) 
        {
            synth->oscillators[i] = osc;
            break;
        }
    }
}

void Synth_Run(Synth_T synth, OutputType_t output_type) 
{
    while (true) 
    {
        int16_t sample = 0;
        for (size_t i = 0; i < 16; ++i) 
        {
            if (synth->oscillators[i] != NULL) 
            {
                Oscillator_Generate(synth->oscillators[i]);
                sample += DoubleBuffer_GetActive(synth->oscillators[i]->audio_buffer);
            }
            else
            {
                break;
            }
        }
        // Replace this line with non-blocking ALSA output
        switch(output_type)
        {
            case OUTPUT_ALSA:
                Output_ALSA(sample);
                printf("Audio buffer ready\n");
                break;
            case OUTPUT_FILE:
                Output_File(sample);
                printf("Audio buffer ready\n");
                break;
            default:
                printf("Audio buffer ready\n");
                break;
        }
        printf("Audio buffer ready\n");
    }
}

uint16_t multiply(uint16_t a, uint16_t b) {
    return a * b;
}

uint16_t add_numbers(uint16_t a, uint16_t b) {
    return a + b;
}