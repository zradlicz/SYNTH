#include "buffer.h"
#include "osc.h"
#include <stdio.h>
#include <stdbool.h>

#define SAMPLE_RATE 44100

static Oscillator_T osc;

void audio_loop() {

    osc = Oscillator_New(WAVEFORM_SQUARE);

    Oscillator_SetFrequency(osc, 440.0);
    Oscillator_SetAmplitude(osc, 20000);

    while (true) {
        Oscillator_Generate(osc);
        // Replace this line with non-blocking ALSA output
        printf("Audio buffer ready\n");
    }
}

int main() {
    printf("Starting audio generation\n");
    audio_loop();
    return 0;
}
