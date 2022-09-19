#include <comn/hdr/gn_lstnr_cfg_lst_pop.h>

/*
 * TODO: Add description.
 */

bool
gn_lstnr_cfg_lst_pop (gn_lstnr_cfg_lst_s * const lst)
{
  switch (lst->len) {
    case 0: {
      return true;
    }
    case 1: {
      lst->head = lst->tail = NULL;
      break;
    }
    default: {
      lst->head->next->prev = lst->tail;
      lst->tail->next = lst->head->next;
      lst->head = lst->head->next;
    }
  }

  lst->len--;
  return false;
}
