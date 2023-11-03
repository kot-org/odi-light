#ifndef LIB_LOCK_H
#define LIB_LOCK_H 1

#include "../deps.h"
#include "../types.h"

#define SPINLOCK_INIT {0, NULL}

typedef struct {
    int lock;
    void *last_acquirer;
} odi_spinlock_t;

static inline bool spinlock_test_and_acq(odi_spinlock_t *lock) {
    return __sync_bool_compare_and_swap(&lock->lock, 0, 1);
}

void odi_spinlock_acquire(odi_spinlock_t *lock);

static inline void odi_spinlock_release(odi_spinlock_t *lock) {
    lock->last_acquirer = NULL;
    __atomic_store_n(&lock->lock, 0, __ATOMIC_SEQ_CST);
}

#endif // LIB_LOCK_H
