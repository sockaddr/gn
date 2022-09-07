#ifndef GN_MSTR_MAIN_H
#define GN_MSTR_MAIN_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

char * gn_self_path (uint8_t * const);
void   gn_start_wrkrs (char * const);

#endif // GN_MSTR_MAIN_H
