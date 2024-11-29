#include "double_buffer.h"
#include "oscillator.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define SAMPLE_RATE 44100

static DoubleBuffer audio_buffer;
static Oscillator osc;

void audio_loop() {
    double_buffer_init(&audio_buffer);
    oscillator_init(&osc, SAMPLE_RATE, WAVEFORM_SQUARE);

    oscillator_set_frequency(&osc, 440.0);
    oscillator_set_amplitude(&osc, 20000);

    while (true) {
        int16_t* inactive_buffer = double_buffer_get_inactive(&audio_buffer);
        oscillator_generate(&osc, inactive_buffer, BUFFER_SIZE);
        double_buffer_swap(&audio_buffer);

        // Replace this line with non-blocking ALSA output
        printf("Audio buffer ready\n");
        usleep(100000); // Simulate playback time
    }
}

int main() {
    printf("Starting audio generation\n");
    audio_loop();
    return 0;
}
