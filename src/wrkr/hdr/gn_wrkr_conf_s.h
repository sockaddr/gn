#ifndef GN_WRKR_CONF_S_H
#define GN_WRKR_CONF_S_H

#include <wrkr/hdr/gn_conn_acpt_thrd_conf_list_s.h>
#include <wrkr/hdr/gn_conn_mgmt_thrd_conf_list_s.h>

/*
 * TODO: Add description.
 */

struct gn_wrkr_conf_s
{
  uint16_t                      conn_mgmt_thrd_num; // TODO: Set this from config file. Maybe rename.
  uint8_t                       conn_acpt_thrd_num; // TODO: Set this from config file. Maybe rename.
  gn_conn_acpt_thrd_conf_list_s conn_acpt_thrd_conf_list;
  gn_conn_mgmt_thrd_conf_list_s conn_mgmt_thrd_conf_list;
};

typedef struct gn_wrkr_conf_s gn_wrkr_conf_s;

#endif // GN_WRKR_CONF_S_H