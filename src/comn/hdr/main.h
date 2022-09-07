#ifndef MAIN_H
#define MAIN_H

#include <error.h>
#include <stdbool.h>
#include <string.h>

void gn_mstr_main (void)
  __attribute__((cold));

/* TODO: Maybe add cold attribute. But this function will probably run high performance code,
 * so adding it might not make sense.
 */
void gn_wrkr_main (void);

#endif // MAIN_H
