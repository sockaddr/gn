#include <wrkr/hdr/gn_new_conn_list_pop.h>

/*
 * TODO: Add description.
 */

void
gn_new_conn_list_pop (gn_new_conn_list_s * const list)
{
  switch (list->len) {
    case 0: {
      return;
    }
    case 1: {
      list->head = list->tail = NULL;
      break;
    }
    default: {
      list->head->next->prev = list->tail;
      list->tail->next = list->head->next;
      list->head = list->head->next;
    }
  }

  list->len--;
}
