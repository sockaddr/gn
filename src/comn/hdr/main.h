#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t gn_mstr_main (void)
  __attribute__((cold)) __attribute__ ((warn_unused_result));

/*
 * TODO: Maybe add cold attribute. But this function will probably run high performance code, so adding it might not
 * make sense because GCC optimizes cold functions for size rather than speed.
 */
void gn_wrkr_main (const char * const);

#endif // MAIN_H
