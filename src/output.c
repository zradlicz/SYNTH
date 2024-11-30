#include <stdio.h>
#include <stdint.h>

//output to file
void Output_File(int16_t * buffer, size_t size) 
{
    //open file
    FILE *file = fopen("output.wav", "w");
    //write sample to file
    for(size_t i = 0; i < size; i++)
    {
        fprintf(file, "%d", buffer[i]);
    }
    //close file
    fclose(file);
    printf("Audio buffer ready\n");
}

//output to ALSA
void Output_ALSA(int16_t * buffer, size_t size) 
{
    //TODO: implement output to ALSA
    printf("Audio buffer ready\n");
}