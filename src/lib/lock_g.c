#include "lock.h"

__attribute__((noinline)) void odi_spinlock_acquire(odi_spinlock_t *lock) {
    volatile size_t deadlock_counter = 0;
    for (;;) {
        if (odi_spinlock_test_and_acq(lock)) {
            break;
        }
#if defined (__x86_64__)
        __asm__ volatile ("pause");
#endif
    }
    lock->last_acquirer = __builtin_return_address(0);
    return;
}
