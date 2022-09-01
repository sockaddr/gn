#ifndef GN_WRKR_CONF_INIT_H
#define GN_WRKR_CONF_INIT_H

#include <wrkr/hdr/gn_wrkr_conf_s.h>

void gn_conn_acpt_thrd_conf_list_init (gn_conn_acpt_thrd_conf_list_s * const)
  __attribute__((nonnull)) __attribute__((cold));
void gn_conn_mgmt_thrd_conf_list_init (gn_conn_mgmt_thrd_conf_list_s * const)
  __attribute__((nonnull)) __attribute__((cold));

#endif // GN_WRKR_CONF_INIT_H
