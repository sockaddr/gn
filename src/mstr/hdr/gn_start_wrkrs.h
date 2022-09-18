#ifndef GN_START_WRKRS_H
#define GN_START_WRKRS_H

#include <comn/hdr/gn_lstnr_conf_list_s.h>
#include <mstr/hdr/gn_mstr_conf_s.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool gn_start_wrkr (char * const, gn_lstnr_conf_list_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__ ((warn_unused_result));

#endif // GN_START_WRKRS_H
