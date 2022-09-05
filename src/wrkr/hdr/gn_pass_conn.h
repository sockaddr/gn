#ifndef GN_PASS_CONN_H
#define GN_PASS_CONN_H

#include <wrkr/hdr/gn_conn_mgmt_thrd_conf_list_s.h>

bool gn_new_conn_list_push_back (gn_new_conn_list_s * const, gn_conn_s * const)
  __attribute__((nonnull)) __attribute__((hot));

#endif // GN_PASS_CONN_H
