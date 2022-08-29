#ifndef GN_CONN_MGMT_THRD_CONF_S_H
#define GN_CONN_MGMT_THRD_CONF_S_H

#include <pthread.h>

typedef struct gn_conn_mgmt_thrd_conf_s gn_conn_mgmt_thrd_conf_s;

struct gn_conn_mgmt_thrd_conf_s {
  pthread_t thrd_id;
  gn_conn_mgmt_thrd_conf_s * prev;
  gn_conn_mgmt_thrd_conf_s * next;
};

#endif // GN_CONN_MGMT_THRD_CONF_S_H
