#include "buffer.h"
#include <string.h>

struct DoubleBuffer {
    int16_t buffer_a[BUFFER_SIZE];
    int16_t buffer_b[BUFFER_SIZE];
    int16_t* active_buffer;
    int16_t* inactive_buffer;
};

void double_buffer_init(DoubleBuffer* db) {
    memset(db->buffer_a, 0, sizeof(db->buffer_a));
    memset(db->buffer_b, 0, sizeof(db->buffer_b));
    db->active_buffer = db->buffer_a;
    db->inactive_buffer = db->buffer_b;
}

int16_t* double_buffer_get_active(DoubleBuffer* db) {
    return db->active_buffer;
}

int16_t* double_buffer_get_inactive(DoubleBuffer* db) {
    return db->inactive_buffer;
}

void double_buffer_swap(DoubleBuffer* db) {
    int16_t* temp = db->active_buffer;
    db->active_buffer = db->inactive_buffer;
    db->inactive_buffer = temp;
}

void double_buffer_clear(DoubleBuffer* db) {
    memset(db->active_buffer, 0, BUFFER_SIZE * sizeof(int16_t));
    memset(db->inactive_buffer, 0, BUFFER_SIZE * sizeof(int16_t));
}
