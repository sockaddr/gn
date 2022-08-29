#include <wrkr/hdr/gn_conn_acpt_thrd_conf_init.h>

void
gn_conn_acpt_thrd_conf_init (gn_conn_acpt_thrd_conf_s * const conf)
{
  conf->stop = false;
  conf->state = CONN_ACPT_THRD_STOPPED;
  conf->prev = NULL;
  conf->next = NULL;
}
