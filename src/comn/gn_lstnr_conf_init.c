#include <comn/hdr/gn_lstnr_conf_init.h>

void
gn_lstnr_conf_init (gn_lstnr_conf_s * const conf)
{
  conf->fd = -1;
  conf->addr = NULL;
  conf->port = 0;
  conf->prev = NULL;
  conf->next = NULL;
}
