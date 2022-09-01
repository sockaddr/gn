#include <wrkr/hdr/gn_wrkr_conf_init.h>

/*
 * TODO: Add description.
 */

void
gn_wrkr_conf_init (gn_wrkr_conf_s * const conf)
{
  conf->conn_mgmt_thrd_num = 1;
  conf->conn_acpt_thrd_num = 1;
  gn_conn_acpt_thrd_conf_list_init (&conf->conn_acpt_thrd_conf_list);
  gn_conn_mgmt_thrd_conf_list_init (&conf->conn_mgmt_thrd_conf_list);
}
