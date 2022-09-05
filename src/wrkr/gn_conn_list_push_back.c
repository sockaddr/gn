#include <wrkr/hdr/gn_conn_list_push_back.h>

/*
 * TODO: Add description.
 */

bool
gn_conn_list_push_back (gn_conn_list_s * const list, gn_conn_s * const conn)
{
  // list->len is a size_t
  switch (list->len) {
    case SIZE_MAX: {
      return true;
    }
    case 0: {
      list->head = list->tail = conn->prev = conn->next = conn;
      break;
    }
    default: {
      list->tail->next = conn;
      conn->prev = list->tail;
      list->head->prev = conn;
      conn->next = list->head;
      list->tail = conn;
    }
  }

  list->len++;
  return false;
}
