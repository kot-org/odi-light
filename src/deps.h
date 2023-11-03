#ifndef _ODI_DEPENDENCIES_H
#define _ODI_DEPENDENCIES_H

//ODI Dependencies file, your platform must implement this functions.

#include "types.h"

extern uint64_t ODI_DEP_PAGE_SIZE;
extern uint8_t ODI_DEP_MPROTECT_PAGE_CACHE_DISABLE;
extern uint8_t ODI_DEP_MPROTECT_PAGE_WRITE_BIT; 

//Conversion management.
char* odi_dep_itoa(uint64_t value, char * str, int base);
uint64_t odi_dep_atoi(const char * str);

int odi_dep_memcmp(const void *s1, const void *s2, size_t n);
void* odi_dep_memset(void *s, int c, size_t n);
void* odi_dep_memcpy(void *dest, const void *src, size_t n);

//String management.
int odi_dep_strcmp(const char* str1, const char* str2);
int odi_dep_strncmp(const char* str1, const char* str2, int n);
int odi_dep_strlen(const char* str);
char* odi_dep_strncpy(char *dest, const char *src, int n);

//Heap management.
void* odi_dep_malloc(int size);
void odi_dep_free(void* ptr);

//Virtual memory management.
void* odi_dep_get_free_contiguous_virtual_address(size_t size);
//Here the current makes reference to the current process (pml4).
//Maps (size) bytes (starting at page aligned virtual_address) to physical_memory.
void odi_dep_map_current_memory_size(void* virtual_address, void* physical_memory, size_t size);
//Maps the page aligned virtual_address to physical_memory.
void odi_dep_map_current_memory(void* virtual_memory, void* physical_memory);
void odi_dep_mprotect_current(void* address, uint64_t size, uint8_t permissions);
void* odi_dep_request_current_page(void);
void* odi_dep_get_virtual_address(void* address);

//Print management.
void odi_dep_vprintf(const char* format, odi_va_list args);
void odi_dep_vsnprintf(char* buffer, int size, const char* format, odi_va_list args);
void odi_dep_printf(const char* format, ...);

//IO Management. Usually an embedded assembly line does the trick.
void odi_dep_outb(uint16_t port, uint8_t value);
void odi_dep_outw(uint16_t port, uint16_t value);
void odi_dep_outl(uint16_t port, uint32_t value);
uint8_t odi_dep_inb(uint16_t port);
uint16_t odi_dep_inw(uint16_t port);
uint32_t odi_dep_inl(uint16_t port);
void odi_dep_insw(uint16_t port, uint8_t* buffer, int count);
void odi_dep_outsw(uint16_t port, uint8_t *buffer, int count);
void odi_dep_io_wait(void);

#endif