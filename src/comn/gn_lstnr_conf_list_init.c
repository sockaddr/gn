#include <comn/hdr/gn_lstnr_conf_list_init.h>

void
gn_lstnr_conf_list_init (gn_lstnr_cfg_lst_s * const lst)
{
  lst->head = NULL;
  lst->tail = NULL;
  lst->len = 0;
}
