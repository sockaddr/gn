#ifndef GN_WRKR_MAIN_H
#define GN_WRKR_MAIN_H

#include <wrkr/hdr/gn_conn_mgmt_thrd_conf_list_s.h>

void gn_conn_mgmt_thrd_conf_list_init (gn_conn_mgmt_thrd_conf_list_s * const)
  __attribute__((nonnull)) __attribute__((cold));

void gn_start_conn_mgmt_thrds (gn_conn_mgmt_thrd_conf_list_s * const)
  __attribute__((nonnull)) __attribute__((cold));
void gn_stop_conn_mgmt_thrds (gn_conn_mgmt_thrd_conf_list_s * const)
  __attribute__((nonnull)) __attribute__((cold));

#endif // GN_WRKR_MAIN_H
