#include "buffer.h"
#include <string.h>

struct DoubleBuffer_S {
    int16_t active_buffer[BUFFER_SIZE];
    int16_t inactive_buffer[BUFFER_SIZE];
};

DoubleBuffer_T DoubleBuffer_New(void) {
    DoubleBuffer_T db;
    memset(db->active_buffer, 0, sizeof(db->active_buffer));
    memset(db->inactive_buffer, 0, sizeof(db->inactive_buffer));
    return db;
}

int16_t* DoubleBuffer_GetActive(DoubleBuffer_T db) {
    return db->active_buffer;
}

int16_t* DoubleBuffer_GetInactive(DoubleBuffer_T db) {
    return db->inactive_buffer;
}

void DoubleBuffer_UpdateInactive(DoubleBuffer_T db, int16_t* data) {
    memcpy(db->inactive_buffer, data, BUFFER_SIZE * sizeof(int16_t));
}

void DoubleBuffer_Swap(DoubleBuffer_T db) {
    int16_t* temp = db->active_buffer;
    db->active_buffer = db->inactive_buffer;
    db->inactive_buffer = temp;
}

void DoubleBuffer_Clear(DoubleBuffer_T db) {
    memset(db->active_buffer, 0, BUFFER_SIZE * sizeof(int16_t));
    memset(db->inactive_buffer, 0, BUFFER_SIZE * sizeof(int16_t));
}

size_t DoubleBuffer_GetSize(DoubleBuffer_T db) {
    return BUFFER_SIZE;
}
