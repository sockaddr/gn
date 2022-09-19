#include <comn/hdr/gn_lstnr_conf_init.h>

/*
 * TODO: Add description.
 */

void
gn_lstnr_conf_init (gn_lstnr_cfg_s * const cfg)
{
  cfg->fd = -1;
  cfg->addr = NULL;
  cfg->port = 0;
  cfg->prev = NULL;
  cfg->next = NULL;
}
