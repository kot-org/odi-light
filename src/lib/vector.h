#ifndef LIB_VECTOR_H
#define LIB_VECTOR_H 1

#include "../deps.h"
#include "../types.h"

#include "lock.h"

typedef struct {
    void** items;
    uint64_t length;
    odi_spinlock_t lock;
}odi_vector_t;


odi_vector_t* vector_create(void);
uint64_t vector_push(odi_vector_t* vector, void* item);
void vector_remove(odi_vector_t* vector, uint64_t index);
void vector_set(odi_vector_t* vector, uint64_t index, void* item);
void vector_expand(odi_vector_t* vector, uint64_t len);
void* vector_get(odi_vector_t* vector, uint64_t index);
void vector_clear(odi_vector_t* vector);
odi_vector_t* vector_clone(odi_vector_t* vector);

#endif // LIB_VECTOR_H