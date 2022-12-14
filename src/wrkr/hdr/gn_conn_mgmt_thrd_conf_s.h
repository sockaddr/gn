#ifndef GN_CONN_MGMT_THRD_CONF_S_H
#define GN_CONN_MGMT_THRD_CONF_S_H

#include <wrkr/hdr/gn_conn_mgmt_thrd_state_e.h>
#include <wrkr/hdr/gn_new_conn_list_list_s.h>

#include <pthread.h>
#include <stdbool.h>

typedef struct gn_conn_mgmt_thrd_conf_s gn_conn_mgmt_thrd_conf_s;

/*
 * TODO: Add description.
 */

struct gn_conn_mgmt_thrd_conf_s
{
  bool                       stop;
  gn_conn_mgmt_thrd_state_e  state;
  gn_new_conn_list_list_s    new_conn_list_list;
  gn_conn_mgmt_thrd_conf_s * prev;
  gn_conn_mgmt_thrd_conf_s * next;
  pthread_t                  thrd_id;
};

#endif // GN_CONN_MGMT_THRD_CONF_S_H
