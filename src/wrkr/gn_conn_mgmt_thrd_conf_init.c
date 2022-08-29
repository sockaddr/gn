#include <wrkr/hdr/gn_conn_mgmt_thrd_conf_init.h>

void
gn_conn_mgmt_thrd_conf_init (gn_conn_mgmt_thrd_conf_s * const conf)
{
  conf->stop = false;
  conf->state = CONN_MGMT_THRD_STOPPED;
  conf->prev = NULL;
  conf->next = NULL;
}
