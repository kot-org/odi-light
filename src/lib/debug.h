#ifndef ODI_LIB_DEBUG_H
#define ODI_LIB_DEBUG_H 1

void odi_assert_failed(char* expr, int line, char* file);

#define odi_assert(expr) if(expr){ odi_assert_failed(#expr, __LINE__, __FILE__); }

#endif // ODI_LIB_DEBUG_H
