#include <wrkr/hdr/gn_conn_acpt_thrd_conf_list_init.h>

bool
gn_conn_acpt_thrd_conf_list_init (gn_conn_acpt_thrd_conf_list_s * const list)
{
  if (list == NULL) return true;

  list->head = NULL;
  list->tail = NULL;
  list->len = 0;

  return false;
}
