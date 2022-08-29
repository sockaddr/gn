#include <wrkr/hdr/gn_conn_acpt_thrd_conf_list_remove.h>

/*
 * TODO: Add description.
 */

void
gn_conn_acpt_thrd_conf_list_remove (gn_conn_acpt_thrd_conf_list_s * const list,
                                    const gn_conn_acpt_thrd_conf_s * const conf)
{
  switch (list->len) {
    case 0: {
      return;
    }
    case 1: {
      list->head = list->tail = NULL; // TODO: Maybe set conf->prev and next to NULL.
      break;
    }
    default: {
      conf->prev->next = conf->next;
      conf->next->prev = conf->prev;
      if (conf == list->head) list->head = conf->next;
      else if (conf == list->tail) list->tail = conf->prev;
    }
  }

  list->len--;
}
