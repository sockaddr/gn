#include <comn/hdr/gn_lstnr_conf_list_init.h>

void
gn_lstnr_conf_list_init (gn_lstnr_conf_list_s * const list)
{
  list->head = NULL;
  list->tail = NULL;
  list->len = 0;
}
