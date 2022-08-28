#ifndef GN_CONN_MGMT_THRD_CONF_LIST_S_H
#define GN_CONN_MGMT_THRD_CONF_LIST_S_H

#include <wrkr/hdr/gn_conn_mgmt_thrd_conf_s.h>

#include <stdint.h>

struct gn_conn_mgmt_thrd_conf_list_s
{
  gn_conn_mgmt_thrd_conf_s * head;
  gn_conn_mgmt_thrd_conf_s * tail;
  uint16_t                   len;
};

typedef struct gn_conn_mgmt_thrd_conf_list_s gn_conn_mgmt_thrd_conf_list_s;

#endif // GN_CONN_MGMT_THRD_CONF_LIST_S_H
