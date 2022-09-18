#include <wrkr/hdr/gn_wrkr_conf_init.h>

/*
 * TODO: Add description.
 */

bool
gn_wrkr_conf_init (gn_wrkr_conf_s * const conf, gn_lstnr_conf_list_s * const lstnr_conf_list)
{
  if (conf == NULL) return true;

  (void)! gn_conn_acpt_thrd_conf_list_init (&conf->conn_acpt_thrd_conf_list);
  conf->conn_acpt_thrd_num = 1;
  (void)! gn_conn_mgmt_thrd_conf_list_init (&conf->conn_mgmt_thrd_conf_list);
  conf->conn_mgmt_thrd_num = 1;
  conf->lstnr_conf_list = lstnr_conf_list;
  conf->start_wout_conn_acpt_thrds = true;
  conf->start_wout_conn_mgmt_thrds = true;

  return false;
}
