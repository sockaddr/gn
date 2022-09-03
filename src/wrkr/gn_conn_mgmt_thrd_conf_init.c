#include <wrkr/hdr/gn_conn_mgmt_thrd_conf_init.h>

void
gn_conn_mgmt_thrd_conf_init (gn_conn_mgmt_thrd_conf_s * const conf)
{
  conf->stop = false;
  conf->state = CONN_MGMT_THRD_STOPPED;
  gn_new_conn_list_list_init (&conf->new_conn_list_list);
  conf->prev = NULL;
  conf->next = NULL;
}
