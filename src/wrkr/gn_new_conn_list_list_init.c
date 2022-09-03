#include <wrkr/hdr/gn_new_conn_list_list_s.h>

void
gn_new_conn_list_list_init (gn_new_conn_list_list_s * const list)
{
  list->head = NULL;
  list->tail = NULL;
  list->len = 0;
}
