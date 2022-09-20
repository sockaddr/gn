#ifndef GN_WRKR_CFG_INI_H
#define GN_WRKR_CFG_INI_H

#include <wrkr/hdr/gn_wrkr_conf_s.h>

bool gn_conn_acpt_thrd_conf_list_init (gn_conn_acpt_thrd_conf_list_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__ ((warn_unused_result));
bool gn_conn_mgmt_thrd_conf_list_init (gn_conn_mgmt_thrd_conf_list_s * const)
  __attribute__((cold)) __attribute__((nonnull)) __attribute__ ((warn_unused_result));

#endif // GN_WRKR_CFG_INI_H
