#include <wrkr/hdr/gn_wrkr_cfg_ini.h>

/*
 * TODO: Add description.
 */

void
gn_wrkr_cfg_ini (gn_wrkr_conf_s * const wc, gn_lstnr_cfg_lst_s * const lstnr_conf_list)
{
  (void)! gn_conn_acpt_thrd_conf_list_init (&wc->conn_acpt_thrd_conf_list);
  wc->conn_acpt_thrd_num = 1;
  (void)! gn_conn_mgmt_thrd_conf_list_init (&wc->conn_mgmt_thrd_conf_list);
  wc->conn_mgmt_thrd_num = 1;
  wc->lstnr_conf_list = lstnr_conf_list;
  wc->start_wout_conn_acpt_thrds = true;
  wc->start_wout_conn_mgmt_thrds = true;
}
