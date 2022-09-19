#include <comn/hdr/gn_lstnr_cfg_lst_pshb.h>

/*
 * TODO: Add description.
 */

bool
gn_lstnr_cfg_lst_pshb (gn_lstnr_cfg_lst_s * const lst, gn_lstnr_cfg_s * const cfg)
{
  switch (lst->len) {
    case UINT16_MAX: {
      return true;
    }
    case 0: {
      lst->head = lst->tail = cfg->prev = cfg->next = cfg;
      break;
    }
    default: {
      lst->tail->next = cfg;
      cfg->prev = lst->tail;
      lst->head->prev = cfg;
      cfg->next = lst->head;
      lst->tail = cfg;
    }
  }

  lst->len++;
  return false;
}
