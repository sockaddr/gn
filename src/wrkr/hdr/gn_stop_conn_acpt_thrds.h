#ifndef GN_STOP_CONN_ACPT_THRDS_H
#define GN_STOP_CONN_ACPT_THRDS_H

#include <wrkr/hdr/gn_conn_acpt_thrd_conf_list_s.h>

// TODO: Maybe add cold attribute.
void
gn_conn_acpt_thrd_conf_list_remove (gn_conn_acpt_thrd_conf_list_s * const,
                                    const gn_conn_acpt_thrd_conf_s * const)
  __attribute__((nonnull));

#endif // GN_STOP_CONN_ACPT_THRDS_H
