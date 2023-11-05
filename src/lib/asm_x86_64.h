static inline void odi_outb(uint16_t port, uint8_t data) {
    __asm__ volatile("outb %b0, %w1" : : "a" (data), "d" (port));
}

static inline void odi_outw(uint16_t port, uint16_t data) {
    __asm__ volatile("outw %w0, %w1" : : "a" (data), "d" (port));
}

static inline void odi_outl(uint16_t port, uint32_t data) {
	__asm__ volatile("outl %0, %w1" : : "a" (data), "d" (port));
}

static inline uint8_t odi_inb(uint16_t port) {
    uint8_t data;
    __asm__ volatile("inb %w1, %b0" : "=a" (data) : "d" (port));
    return data;
}

static inline uint16_t odi_inw(uint16_t port) {
    uint16_t data;
    __asm__ volatile("inw %w1, %w0" : "=a" (data) : "d" (port));
    return data;
}

static inline uint32_t odi_inl(uint16_t port) {
    uint32_t data;
    __asm__ volatile("inl %w1, %0" : "=a" (data) : "d" (port));
    return data;
}