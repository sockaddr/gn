#ifndef GN_CONN_ACPT_THRD_CONF_S_H
#define GN_CONN_ACPT_THRD_CONF_S_H

#include <wrkr/hdr/gn_conn_acpt_thrd_state_e.h>

#include <pthread.h>
#include <stdbool.h>

typedef struct gn_conn_acpt_thrd_conf_s gn_conn_acpt_thrd_conf_s;

struct gn_conn_acpt_thrd_conf_s {
  bool                       stop;
  gn_conn_acpt_thrd_state_e  state;
  gn_conn_acpt_thrd_conf_s * prev;
  gn_conn_acpt_thrd_conf_s * next;
  pthread_t                  thrd_id;
};

#endif // GN_CONN_ACPT_THRD_CONF_S_H
