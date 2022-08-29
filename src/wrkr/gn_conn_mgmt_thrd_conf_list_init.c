#include <wrkr/hdr/gn_conn_mgmt_thrd_conf_list_init.h>

void
gn_conn_mgmt_thrd_conf_list_init (gn_conn_mgmt_thrd_conf_list_s * const list)
{
  list->head = NULL;
  list->tail = NULL;
  list->len = 0;
}
