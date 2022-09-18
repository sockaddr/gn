#include <comn/hdr/gn_lstnr_cfg_lst_ini.h>

void
gn_lstnr_cfg_lst_ini (gn_lstnr_cfg_lst_s * const lst)
{
  lst->head = NULL;
  lst->tail = NULL;
  lst->len = 0;
}
