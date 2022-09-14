#ifndef GN_START_WRKRS_H
#define GN_START_WRKRS_H

#include <mstr/hdr/gn_mstr_conf_s.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool gn_start_wrkr (char * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__ ((warn_unused_result));

#endif // GN_START_WRKRS_H
