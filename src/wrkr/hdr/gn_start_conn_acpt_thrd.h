#ifndef GN_START_CONN_ACPT_THRD_H
#define GN_START_CONN_ACPT_THRD_H

#include <wrkr/hdr/gn_wrkr_cfg_s.h>

void * gn_conn_acpt_thrd (void * const);

bool gn_conn_acpt_thrd_conf_list_push_back (gn_conn_acpt_thrd_conf_list_s * const, gn_conn_acpt_thrd_conf_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__ ((warn_unused_result));

#endif // GN_START_CONN_ACPT_THRD_H
