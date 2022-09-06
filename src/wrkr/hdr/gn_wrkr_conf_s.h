#ifndef GN_WRKR_CONF_S_H
#define GN_WRKR_CONF_S_H

#include <wrkr/hdr/gn_conn_acpt_thrd_conf_list_s.h>
#include <wrkr/hdr/gn_conn_mgmt_thrd_conf_list_s.h>

/*
 * TODO: Add description.
 */

struct gn_wrkr_conf_s
{
  gn_conn_acpt_thrd_conf_list_s conn_acpt_thrd_conf_list; // TODO: Maybe rename.
  uint8_t                       conn_acpt_thrd_num; // TODO: Set this from config file. Maybe rename.
  gn_conn_mgmt_thrd_conf_list_s conn_mgmt_thrd_conf_list; // TODO: Maybe rename.
  uint16_t                      conn_mgmt_thrd_num; // TODO: Set this from config file. Maybe rename.
  bool                          start_wout_conn_acpt_thrds; // TODO: Set this from config file. Maybe rename.
  bool                          start_wout_conn_mgmt_thrds; // TODO: Set this from config file. Maybe rename.
};

typedef struct gn_wrkr_conf_s gn_wrkr_conf_s;

#endif // GN_WRKR_CONF_S_H
