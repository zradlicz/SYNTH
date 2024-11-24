#include <stdio.h>
#include <alsa/asoundlib.h>
#include "synth.h"

#ifndef UNIT_TEST
int main() {
    printf("Welcome to the Synthesizer Project!\n");
    printf("ALSA library initialized successfully\n");
    
    // Correct the printf usage with a format string for integers
    printf("add_numbers result: %d\n", add_numbers(10, 20));
    printf("multiply result: %d\n", multiply(10, 20));

    return 0;
}
#endif