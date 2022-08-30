#include <wrkr/hdr/gn_conn_acpt_thrd_conf_init.h>

void
gn_conn_acpt_thrd_conf_init (gn_conn_acpt_thrd_conf_s * const            conf,
                             const gn_conn_mgmt_thrd_conf_list_s * const list)
{
  conf->conn_mgmt_thrd_conf_list = list;
  conf->stop = false;
  conf->state = CONN_ACPT_THRD_STOPPED;
  conf->prev = NULL;
  conf->next = NULL;
}
