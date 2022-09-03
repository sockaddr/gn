#include <wrkr/hdr/gn_new_conn_list_s.h>

void
gn_new_conn_list_init (gn_new_conn_list_s * const list)
{
  list->lock = (uintptr_t)NULL;
  list->head = NULL;
  list->tail = NULL;
  list->len  = 0;
  list->prev = NULL;
  list->next = NULL;
}
