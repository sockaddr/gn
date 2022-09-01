#include <wrkr/hdr/gn_wrkr_conf_init.h>

void
gn_wrkr_conf_init (gn_wrkr_conf_s * const conf)
{
  conf->conn_mgmt_thrd_num = 1;
  conf->conn_acpt_thrd_num = 1;
}
