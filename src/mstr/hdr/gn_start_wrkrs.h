#ifndef GN_START_WRKRS_H
#define GN_START_WRKRS_H

#include <mstr/hdr/gn_mstr_cfg_s.h>

#include <stdbool.h>
#include <stdint.h>

void gn_lstnrs_send (const int, const gn_lstnr_cfg_lst_s * const)
  __attribute__((cold)) __attribute__((nonnull));

bool gn_start_wrkr (gn_mstr_cfg_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__ ((warn_unused_result));

int gn_wrkr_acpt (const int)
  __attribute__((cold)) __attribute__ ((warn_unused_result));

#endif // GN_START_WRKRS_H
