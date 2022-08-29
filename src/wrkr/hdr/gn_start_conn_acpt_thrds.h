#ifndef GN_START_CONN_ACPT_THRDS_H
#define GN_START_CONN_ACPT_THRDS_H

#include <wrkr/hdr/gn_conn_acpt_thrd_conf_list_s.h>

#include <error.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void * gn_conn_acpt_thrd (void * const);

void
gn_conn_acpt_thrd_conf_init (gn_conn_acpt_thrd_conf_s * const)
  __attribute__((cold));

bool   gn_conn_acpt_thrd_conf_list_push_back (gn_conn_acpt_thrd_conf_list_s * const,
                                              gn_conn_acpt_thrd_conf_s * const)
  __attribute__ ((warn_unused_result));

#endif // GN_START_CONN_ACPT_THRDS_H
