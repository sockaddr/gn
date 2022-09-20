#ifndef GN_START_CONN_MGMT_THRDS_H
#define GN_START_CONN_MGMT_THRDS_H

#include <wrkr/hdr/gn_wrkr_cfg_s.h>

#include <error.h>
#include <stdbool.h>
#include <stdlib.h>

void gn_conn_mgmt_thrd_conf_init (gn_conn_mgmt_thrd_conf_s * const)
  __attribute__((cold)) __attribute__((nonnull));

void gn_new_conn_list_init (gn_new_conn_list_s * const)
  __attribute__((cold)) __attribute__((nonnull));

bool gn_new_conn_list_list_push_back (gn_new_conn_list_list_s * const, gn_new_conn_list_s * const)
  __attribute__((cold)) __attribute__((nonnull));

bool gn_start_conn_mgmt_thrd (gn_wrkr_cfg_s * const, gn_conn_mgmt_thrd_conf_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__ ((warn_unused_result));

#endif // GN_START_CONN_MGMT_THRDS_H
