#include "vector.h"

odi_vector_t* vector_create(void) {
    odi_vector_t* vector = (odi_vector_t*)odi_dep_malloc(sizeof(odi_vector_t));
    vector->items = NULL;
    vector->length = 0;
    vector->lock = (odi_spinlock_t){};
    return vector;
}

odi_vector_t* vector_clone(odi_vector_t* vector) {
    odi_spinlock_acquire(&vector->lock);
    void** new_vector = (void**)odi_dep_malloc((size_t)(vector->length * 8));
    odi_dep_memcpy(new_vector, vector->items, vector->length * 8);
    odi_spinlock_release(&vector->lock);
    return (odi_vector_t*)new_vector;
}

void vector_expand(odi_vector_t* vector, uint64_t len) {
    odi_spinlock_acquire(&vector->lock);
    void** temp = (void**)odi_dep_malloc((size_t)((vector->length + len) * 8));
    odi_dep_memcpy(temp, vector->items, vector->length * 8);
    odi_dep_free(vector->items);
    vector->items = temp;
    vector->length+=len;
    odi_spinlock_release(&vector->lock);
}

uint64_t vector_push(odi_vector_t* vector, void* item) {
    if (vector->items == NULL) {
        odi_spinlock_acquire(&vector->lock);
        vector->items = (void**) odi_dep_malloc(8);
        vector->length = 1;
        *(void**)(vector->items) = item;
        odi_spinlock_release(&vector->lock);
    } else {
        vector_expand(vector, 1);
        odi_spinlock_acquire(&vector->lock);
        *(void**)(vector->items + vector->length - 1) = item;
        odi_spinlock_release(&vector->lock);
    }
    return vector->length - 1;
}

void* vector_get(odi_vector_t* vector, uint64_t index) {
    return *(void**)(vector->items + index);
}

void vector_set(odi_vector_t* vector, uint64_t index, void* item) {
    if (index < vector->length) {
        *(void**)(vector->items + index) = item;
    }
}

void vector_clear(odi_vector_t* vector) {
    if (vector->items != NULL) {
        odi_spinlock_acquire(&vector->lock);
        odi_dep_free(vector->items);
        vector->items = NULL;
        vector->length = 0;
        odi_spinlock_release(&vector->lock);
    }
}

void vector_remove(odi_vector_t* vector, uint64_t index) {
    if (vector->items != NULL && index < vector->length) {
        if (vector->length == 1) {
            vector_clear(vector);
        } else if (vector->length != 0) {
            odi_spinlock_acquire(&vector->lock);
            void** temp = (void**) odi_dep_malloc((size_t)((vector->length - 1) * 8));
            if (index != 0) { odi_dep_memcpy(temp, vector->items, index * 8); }
            odi_dep_memcpy(temp, vector->items + index * 8, ((vector->length - 1) * 8) - index * 8);
            odi_dep_free(vector->items);
            vector->items = temp;
            vector->length--;
            odi_spinlock_release(&vector->lock);
        }
    }
}