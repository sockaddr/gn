#include <comn/hdr/gn_lstnr_conf_list_push_back.h>

bool
gn_lstnr_conf_list_push_back (gn_lstnr_conf_list_s * const list,
                              gn_lstnr_conf_s * const      conf)
{
  switch (list->len) {
    case UINT16_MAX: {
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
