#include <wrkr/hdr/gn_new_conn_list_push_back.h>

/*
 * TODO: Add description.
 */

bool
gn_new_conn_list_push_back (gn_new_conn_list_s * const list, gn_conn_s * const conn)
{
  // list->len is a uint8_t
  switch (list->len) {
    case UINT8_MAX: {
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
