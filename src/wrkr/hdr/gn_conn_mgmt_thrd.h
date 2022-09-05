#ifndef GN_CONN_MGMT_THRD_H
#define GN_CONN_MGMT_THRD_H

#include <wrkr/hdr/gn_conn_list_s.h>
#include <wrkr/hdr/gn_conn_mgmt_thrd_conf_s.h>

void gn_conn_list_init (gn_conn_list_s * const)
  __attribute__((nonnull));

void gn_get_new_conns (gn_new_conn_list_list_s * const, gn_conn_list_s * const)
  __attribute__((nonnull)) __attribute__((hot));

#endif // GN_CONN_MGMT_THRD_H
