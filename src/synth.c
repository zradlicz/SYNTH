#include "synth.h"
#include "osc.h"
#include "buffer.h"
#include "output.h"
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

    pthread_mutex_t * mutex;
    pthread_cond_t * cond;
};

// Audio generation thread
static void* Synth_GenerateAudio(void * arg) {
    Synth_T synth = (Synth_T)arg;
    //while the synth is running
    while (synth->running) {
        //lock the mutex
        pthread_mutex_lock(synth->mutex);
        //create a temporary buffer and a mixed buffer
        //temporary buffer is used to store the output of each oscillator
        //mixed buffer is used to store the sum of all oscillator outputs
        int16_t temp_buffer[BUFFER_SIZE];
        int16_t mixed_buffer[BUFFER_SIZE];

        memset(temp_buffer, 0, BUFFER_SIZE * sizeof(int16_t));
        memset(mixed_buffer, 0, BUFFER_SIZE * sizeof(int16_t));

        //generate audio for each oscillator
        for(size_t i = 0; i < MAX_OSCILLATORS; i++) 
        {
            if(synth->oscillators[i] != NULL)
            {
                //for each oscilaltor, generate audio and add it to the mixed buffer
                Oscillator_Generate(synth->oscillators[i], temp_buffer, sizeof(temp_buffer));
                mixed_buffer[i] += temp_buffer[i];
            }
            else
            {
                break;
            }
        }

        // Update inactive buffer with mixed buffer which is combination
        // of all oscillator outputs
        DoubleBuffer_UpdateInactive(synth->buffer, mixed_buffer);

        // Swap inactive buffer to active buffer. The inactive buffer now
        // becomes the active buffer and vice versa
        DoubleBuffer_Swap(synth->buffer);

        // active buffer is ready to be output
        pthread_cond_signal(synth->cond);
        //unlock the mutex once the active buffer is ready
        pthread_mutex_unlock(synth->mutex);
    }
}

// Audio output thread
static void* Synth_OutputAudio(void * arg) {
    Synth_T synth = (Synth_T)arg;
    while (synth->running) {
        //lock the mutex while the audio is outputting
        pthread_mutex_lock(synth->mutex);

        // Wait for active buffer to be populated
        pthread_cond_wait(synth->cond, synth->mutex);

        //creat temp buffer to store active buffer
        int16_t active_buffer[BUFFER_SIZE];
        // Output the active buffer
        DoubleBuffer_GetActive(synth->buffer, active_buffer, sizeof(active_buffer));
        
        Output_File(active_buffer, sizeof(active_buffer));

        printf("Outputting audio...\n");

        pthread_mutex_unlock(synth->mutex);
    }
}

Synth_T Synth_New(void) {
    static struct Synth_S synth;
    Synth_T me = &synth;
    me->buffer = DoubleBuffer_New();
    me->running = false;
    //pthread_mutex_init(me->mutex, NULL);
    //pthread_cond_init(me->cond, NULL);
    return me;
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
