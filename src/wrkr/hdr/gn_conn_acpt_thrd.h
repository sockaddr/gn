#ifndef GN_CONN_ACPT_THRD_H
#define GN_CONN_ACPT_THRD_H

#include <comn/hdr/gn_lstnr_conf_list_s.h>
#include <wrkr/hdr/gn_conn_acpt_thrd_conf_s.h>
#include <wrkr/hdr/gn_conn_s.h>

void gn_lstnr_conf_list_init (gn_lstnr_conf_list_s * const);

void gn_conn_init (gn_conn_s * const)
  __attribute__((hot)) __attribute__((nonnull));

bool gn_pass_conn (const gn_conn_mgmt_thrd_conf_list_s * const, gn_conn_s * const)
  __attribute__((hot)) __attribute__((nonnull)) __attribute__ ((warn_unused_result)) ;

#endif // GN_CONN_ACPT_THRD_H
