#ifndef GN_CONN_MGMT_THRD_CONF_S_H
#define GN_CONN_MGMT_THRD_CONF_S_H

#include <pthread.h>

struct gn_conn_mgmt_thrd_conf_s {
  pthread_t thrd_id;
};

typedef struct gn_conn_mgmt_thrd_conf_s gn_conn_mgmt_thrd_conf_s;

#endif // GN_CONN_MGMT_THRD_CONF_S_H
