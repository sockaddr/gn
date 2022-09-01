#ifndef GN_STOP_CONN_MGMT_THRDS_H
#define GN_STOP_CONN_MGMT_THRDS_H

#include <wrkr/hdr/gn_wrkr_conf_s.h>

// TODO: Maybe add cold attribute.
void
gn_conn_mgmt_thrd_conf_list_remove (gn_conn_mgmt_thrd_conf_list_s * const,
                                    const gn_conn_mgmt_thrd_conf_s * const)
  __attribute__((nonnull));

#endif // GN_STOP_CONN_MGMT_THRDS_H
