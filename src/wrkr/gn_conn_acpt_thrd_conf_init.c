#include <wrkr/hdr/gn_conn_acpt_thrd_conf_init.h>

void
gn_conn_acpt_thrd_conf_init (gn_conn_acpt_thrd_conf_s * const conf,
                             const gn_wrkr_conf_s * const     wc)
{
  conf->conn_mgmt_thrd_conf_list = &wc->conn_mgmt_thrd_conf_list;
  conf->lstnr_conf_list = wc->lstnr_conf_list;
  conf->stop = false;
  conf->state = CONN_ACPT_THRD_STOPPED;
  conf->prev = NULL;
  conf->next = NULL;
}
