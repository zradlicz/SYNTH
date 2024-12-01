#include "buffer.h"
#include <string.h>

struct DoubleBuffer_S {
    int16_t active_buffer[BUFFER_SIZE];
    int16_t inactive_buffer[BUFFER_SIZE];
};

DoubleBuffer_T DoubleBuffer_New(void) {
    static struct DoubleBuffer_S db;
    DoubleBuffer_T me = &db;
    memset(me->active_buffer, 0, sizeof(me->active_buffer));
    memset(me->inactive_buffer, 0, sizeof(me->inactive_buffer));
    return me;
}

void DoubleBuffer_GetActive(DoubleBuffer_T db, int16_t* data, size_t size) {
    memcpy(data, db->active_buffer, size);
}

void DoubleBuffer_GetInactive(DoubleBuffer_T db, int16_t* data, size_t size) {
    memcpy(data, db->inactive_buffer, size);
}

void DoubleBuffer_UpdateInactive(DoubleBuffer_T db, int16_t* data) {
    memcpy(db->inactive_buffer, data, sizeof(data));
}

void DoubleBuffer_Swap(DoubleBuffer_T db) {
     // Temporary buffer to hold one array during the swap
    int16_t temp[BUFFER_SIZE];

    // Swap using memcpy
    memcpy(temp, db->active_buffer, BUFFER_SIZE * sizeof(int16_t));
    memcpy(db->active_buffer, db->inactive_buffer, BUFFER_SIZE * sizeof(int16_t));
    memcpy(db->inactive_buffer, temp, BUFFER_SIZE * sizeof(int16_t));
}

void DoubleBuffer_Clear(DoubleBuffer_T db) {
    memset(db->active_buffer, 0, BUFFER_SIZE * sizeof(int16_t));
    memset(db->inactive_buffer, 0, BUFFER_SIZE * sizeof(int16_t));
}

size_t DoubleBuffer_GetSize(DoubleBuffer_T db) {
    return BUFFER_SIZE;
}
