#ifndef GN_WRKR_MAIN_H
#define GN_WRKR_MAIN_H

#include <wrkr/hdr/gn_wrkr_conf_s.h>

void
gn_wrkr_conf_init (gn_wrkr_conf_s * const)
  __attribute__((nonnull)) __attribute__((cold));

void gn_start_conn_acpt_thrds (gn_wrkr_conf_s * const)
  __attribute__((nonnull)) __attribute__((cold));
void gn_start_conn_mgmt_thrds (gn_wrkr_conf_s * const)
  __attribute__((nonnull)) __attribute__((cold));

void gn_stop_conn_acpt_thrds (gn_wrkr_conf_s * const)
  __attribute__((nonnull)) __attribute__((cold));
void gn_stop_conn_mgmt_thrds (gn_wrkr_conf_s * const)
  __attribute__((nonnull)) __attribute__((cold));

#endif // GN_WRKR_MAIN_H
