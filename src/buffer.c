#include "buffer.h"
#include <string.h>

struct DoubleBuffer_S {
    int16_t buffer_a[BUFFER_SIZE];
    int16_t buffer_b[BUFFER_SIZE];
    int16_t* active_buffer;
    int16_t* inactive_buffer;
};

DoubleBuffer_T DoubleBuffer_New(void) {
    DoubleBuffer_T db;
    memset(db->buffer_a, 0, sizeof(db->buffer_a));
    memset(db->buffer_b, 0, sizeof(db->buffer_b));
    db->active_buffer = db->buffer_a;
    db->inactive_buffer = db->buffer_b;
    return db;
}

int16_t* DoubleBuffer_GetActive(DoubleBuffer_T db) {
    return db->active_buffer;
}

int16_t* DoubleBuffer_GetInactive(DoubleBuffer_T db) {
    return db->inactive_buffer;
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
