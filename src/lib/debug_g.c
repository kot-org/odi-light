#include "../deps.h"

void odi_assert_failed(char* expr, int line, char* file){
    odi_dep_printf("Assert failed : %s, at : %s:%d", expr, line, file);
}