#ifndef ODI_LIB_VECTOR_H
#define ODI_LIB_VECTOR_H 1

#include "../deps.h"
#include "../types.h"

#include "lock.h"

typedef struct {
    void** items;
    uint64_t length;
    odi_spinlock_t lock;
} odi_vector_t;


odi_vector_t* odi_vector_create(void);
uint64_t odi_vector_push(odi_vector_t* vector, void* item);
void odi_vector_remove(odi_vector_t* vector, uint64_t index);
void odi_vector_set(odi_vector_t* vector, uint64_t index, void* item);
void odi_vector_expand(odi_vector_t* vector, uint64_t len);
void* odi_vector_get(odi_vector_t* vector, uint64_t index);
void odi_vector_clear(odi_vector_t* vector);
odi_vector_t* odi_vector_clone(odi_vector_t* vector);

#endif // ODI_LIB_VECTOR_H