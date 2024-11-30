#include "synth.h"
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MAX_OSCILLATORS 16
struct Synth_S {
    DoubleBuffer_T buffer;
    Oscillator_T oscillators[MAX_OSCILLATORS];
    
    pthread_t generator_thread;
    pthread_t output_thread;
    
    bool running;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

// Audio generation thread
static void Synth_GenerateAudio(Synth_T synth) {
    while (synth->running) {
        pthread_mutex_lock(synth->mutex);

        int16_t[BUFFER_SIZE] temp_buffer;
        int16_t[BUFFER_SIZE] mixed_buffer;

        memset(temp_buffer, 0, BUFFER_SIZE * sizeof(int16_t));
        memset(mixed_buffer, 0, BUFFER_SIZE * sizeof(int16_t));

        for(size_t i = 0; i < MAX_OSCILLATORS; i++) 
        {
            if(synth->oscillators[i] != NULL)
            {
                Oscillator_Generate(oscillators[i], temp_buffer, sizeof(temp_buffer));
                mixed_buffer[i] += temp_buffer[i];
            }
            else
            {
                break;
            }
        }

        DoubleBuffer_UpdateInactive(synth->buffer, mixed_buffer);

        // Swap inactive buffer to active buffer
        DoubleBuffer_Swap(synth->buffer);

        // Signal buffer is ready
        pthread_cond_signal(&synth->cond);
        pthread_mutex_unlock(&synth->mutex);
    }
}

// Audio output thread
static void Synth_OutputAudio(Synth_T synth) {
    while (synth->running) {
        pthread_mutex_lock(&synth->mutex);

        // Wait for buffer to be ready
        pthread_cond_wait(&synth->cond, &synth->mutex);

        // Output the active buffer
        int16_t* active_buffer = DoubleBuffer_GetActive(synth->buffer);
        
        Output_File(active_buffer);

        printf("Outputting audio...\n");

        pthread_mutex_unlock(&synth->mutex);
    }
}

Synth_T Synth_New(void) {
    Synth_T synth;
    synth->buffer = DoubleBuffer_New();
    synth->running = false;
    pthread_mutex_init(synth->mutex, NULL);
    pthread_cond_init(synth->cond, NULL);
    return synth;
}

void Synth_AddOscillator(Synth_T synth, Oscillator_T osc) {
    for(size_t i = 0; i < MAX_OSCILLATORS; i++) 
    {
        if(synth->oscillators[i] == NULL)
        {
            synth->oscillators[i] = osc;
            break;
        }
    }
}

void Synth_Start(Synth_T synth) {
    if (synth->running) return;
    synth->running = true;

    pthread_create(&synth->generator_thread, NULL, Synth_GenerateAudio, synth);
    pthread_create(&synth->output_thread, NULL, Synth_OutputAudio, synth);
}

void Synth_Stop(Synth_T synth) {
    if (!synth->running) return;
    synth->running = false;

    pthread_join(synth->generator_thread, NULL);
    pthread_join(synth->output_thread, NULL);
}
