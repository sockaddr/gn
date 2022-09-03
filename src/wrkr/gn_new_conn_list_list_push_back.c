#include <wrkr/hdr/gn_new_conn_list_list_push_back.h>

/*
 * TODO: Add description.
 */

bool
gn_new_conn_list_list_push_back (gn_new_conn_list_list_s * const list, gn_new_conn_list_s * const new)
{
  // list->len is a uint8_t
  switch (list->len) {
    case UINT8_MAX: {
      return true;
    }
    case 0: {
      list->head = list->tail = new->prev = new->next = new;
      break;
    }
    default: {
      list->tail->next = new;
      new->prev = list->tail;
      list->head->prev = new;
      new->next = list->head;
      list->tail = new;
    }
  }

  list->len++;
  return false;
}
