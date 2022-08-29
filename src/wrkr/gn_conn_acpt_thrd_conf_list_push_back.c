#include <wrkr/hdr/gn_conn_acpt_thrd_conf_list_push_back.h>

/*
 * TODO: Add description.
 */

bool
gn_conn_acpt_thrd_conf_list_push_back (gn_conn_acpt_thrd_conf_list_s * const list,
                                       gn_conn_acpt_thrd_conf_s * const      conf)
{
  // list->len is a uint16_t
  switch (list->len) {
    case UINT8_MAX: {
      return true;
    }
    case 0: {
      list->head = list->tail = conf->prev = conf->next = conf;
      break;
    }
    default: {
      list->tail->next = conf;
      conf->prev = list->tail;
      list->head->prev = conf;
      conf->next = list->head;
      list->tail = conf;
    }
  }

  list->len++;
  return false;
}
