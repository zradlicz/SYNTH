#include <stdio.h>
#include <stdint.h>

//output to file
void Output_File(int16_t sample) 
{
    //open file
    FILE *file = fopen("output.wav", "w");
    //write sample to file
    fprintf(file, "%d", sample);
    //close file
    fclose(file);
    printf("Audio buffer ready\n");
}

//output to ALSA
void Output_ALSA(int16_t sample) 
{
    //TODO: implement output to ALSA
    printf("Audio buffer ready\n");
}